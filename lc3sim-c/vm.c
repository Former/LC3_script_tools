//
//  Created by Ryan Pendleton on 6/28/18.
//  Copyright © 2018 Ryan Pendleton. All rights reserved.
//

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>

#include "vm.h"
#include "types.h"

#ifdef TRACE
#   define DEBUG_TRACE printf
#else
#   define DEBUG_TRACE(...)
#endif

#ifdef LC3_32BIT
extern unsigned char lc3os32_obj[];
extern unsigned int lc3os32_obj_len;
#define lc3os_bin_data lc3os32_obj
#define lc3os_bin_data_len lc3os32_obj_len
#define swap swap32

static uint32_t swap32(uint32_t val) {
    return (val << 8 * 3) | ((val << 8) & 0x00FF0000) | ((val >> 8) & 0x0000FF00) | (val >> 8 * 3);
}
#else
extern unsigned char lc3os_obj[];
extern unsigned int lc3os_obj_len;
#define lc3os_bin_data lc3os_obj
#define lc3os_bin_data_len lc3os_obj_len
#define swap swap16

static uint16_t swap16(uint16_t val) {
    return (val << 8) | (val >> 8);
}
#endif


// MARK: - Types

enum {
    VM_ADDR_MAX     = LC3_MAX_MEMORY_ADDRES,
    VM_ADDR_INITIAL = 0x3000,
    VM_SIGN_BIT     = 1 << LC3_SIGN_BIT_INDEX,
    VM_STATUS_BIT   = 1 << LC3_STATUS_BIT_INDEX,
};

typedef lc3_register_type vm_byte;
typedef lc3_mem_addres_type vm_addr;

typedef enum {
    VM_OPCODE_ADD  = 0b0001,
    VM_OPCODE_AND  = 0b0101,
    VM_OPCODE_BR   = 0b0000,
    VM_OPCODE_JMP  = 0b1100,
    VM_OPCODE_JSR  = 0b0100,
    VM_OPCODE_LD   = 0b0010,
    VM_OPCODE_LDI  = 0b1010,
    VM_OPCODE_LDR  = 0b0110,
    VM_OPCODE_LEA  = 0b1110,
    VM_OPCODE_NOT  = 0b1001,
    VM_OPCODE_RTI  = 0b1000,
    VM_OPCODE_ST   = 0b0011,
    VM_OPCODE_STI  = 0b1011,
    VM_OPCODE_STR  = 0b0111,
    VM_OPCODE_TRAP = 0b1111,
    VM_OPCODE_RESERVED = 0b1101,
} vm_opcode;

typedef enum {
    VM_ADDR_KBSR = 0xfe00,
    VM_ADDR_KBDR = 0xfe02,
    VM_ADDR_DSR  = 0xfe04,
    VM_ADDR_DDR  = 0xfe06,
    VM_ADDR_MCR  = 0xfffe,
} vm_addr_special;

typedef enum {
    VM_REG_0 = 0,
    VM_REG_1,
    VM_REG_2,
    VM_REG_3,
    VM_REG_4,
    VM_REG_5,
    VM_REG_6,
    VM_REG_7,
    VM_REG_PC,
    VM_REG_PSR,
    VM_REG_COUNT
} vm_reg;

typedef enum {
    VM_FLAG_NEGATIVE = 0b100,
    VM_FLAG_ZERO     = 0b010,
    VM_FLAG_POSITIVE = 0b001,
} vm_flag;

struct vm_impl {
    vm_byte mem[VM_ADDR_MAX];
    vm_byte reg[VM_REG_COUNT];
};

// MARK: - Helpers

static vm_byte sextend(vm_byte val, vm_byte n) {
    vm_byte m = 1 << (n - 1);
    val &= ((1 << n) - 1);
    return (val ^ m) - m;
}

// MARK: - Creation

vm_ctx vm_create(void) {
    vm_ctx vm = calloc(1, sizeof(struct vm_impl));

    vm->reg[VM_REG_PC] = VM_ADDR_INITIAL;
    vm->reg[VM_REG_PSR] = VM_FLAG_ZERO;
    vm->mem[VM_ADDR_MCR] = VM_STATUS_BIT;

    return vm;
}

void vm_destroy(vm_ctx vm) {
    free(vm);
}

// MARK: - Memory

static vm_byte vm_read(vm_ctx vm, vm_addr addr) {
    assert(vm != NULL);

    if (addr == VM_ADDR_KBSR) {
        static fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        return select(1, &readfds, NULL, NULL, &timeout) ? VM_STATUS_BIT : 0;
    }
    else if (addr == VM_ADDR_KBDR) {
        if (vm_read(vm, VM_ADDR_KBSR)) {
            return getchar();
        }
        else {
            return 0;
        }
    }
    else if (addr == VM_ADDR_DSR) {
        return VM_STATUS_BIT;
    }
    else if (addr == VM_ADDR_DDR) {
        return 0;
    }

    return vm->mem[addr];
}

static void vm_write(vm_ctx vm, vm_addr addr, vm_byte val) {
    assert(vm != NULL);

    if (addr == VM_ADDR_KBSR || addr == VM_ADDR_KBDR || addr == VM_ADDR_DSR) {
        return;
    }
    else if (addr == VM_ADDR_DDR) {
        putchar(val);
        fflush(stdout);
        return;
    }

    vm->mem[addr] = val;
}

void vm_load_os(vm_ctx vm) {
    vm_result res = vm_load_data(vm, lc3os_bin_data, lc3os_bin_data_len);
    assert(res == VM_SUCCESS);
}

vm_result vm_load_file(vm_ctx vm, const char *file) {
    int fd, ret;
    struct stat statbuf;
    unsigned char *data;

    if ((fd = open(file, O_RDONLY)) < 0) {
        return VM_INPUT_NOT_FOUND;
    }

    if ((ret = fstat(fd, &statbuf)) < 0) {
        return VM_INPUT_NOT_FOUND;
    }

    if ((data = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        return VM_INPUT_NOT_FOUND;
    }

    vm_result result = vm_load_data(vm, data, statbuf.st_size);

    munmap(data, statbuf.st_size);
    close(fd);
    
    return result;
}

vm_result vm_load_data(vm_ctx vm, unsigned const char *data, size_t length) {
    typedef vm_byte vm_byte_load;
    assert(vm != NULL);

    vm_addr load_addr = swap(*((vm_byte_load*)data));
    size_t load_length = (length - sizeof(vm_byte_load)) / sizeof(vm_byte_load);

    assert(load_addr + load_length < VM_ADDR_MAX);

    vm_byte *dest = vm->mem + load_addr;
    vm_byte_load *source = (vm_byte_load*)(data + sizeof(vm_byte_load));

    if (dest + load_length >= vm->mem + VM_ADDR_MAX) {
        return VM_INPUT_TOO_LARGE;
    }

    while (load_length-- > 0) {
        *(dest++) = swap(*(source++));
    }

    vm->reg[VM_REG_PC] = load_addr;

    return VM_SUCCESS;
}

// MARK: - Execution

static vm_flag vm_sign_flag(vm_reg val) {
    if (val == 0) {
        return VM_FLAG_ZERO;
    }
    else if (val & VM_SIGN_BIT) {
        return VM_FLAG_NEGATIVE;
    }
    else {
        return VM_FLAG_POSITIVE;
    }
}

static void vm_setcc(vm_ctx vm, vm_reg reg) {
    assert(vm != NULL);

    vm->reg[VM_REG_PSR] = vm_sign_flag(vm->reg[reg]);
}

static vm_result vm_perform(vm_ctx vm, vm_byte instr) {
    assert(vm != NULL);

    DEBUG_TRACE("DEBUG vm_perform instr %x REG_PC %x\n", instr, vm->reg[VM_REG_PC]);

    switch ((vm_opcode)(instr >> 12)) {
        case VM_OPCODE_ADD: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_reg sr1 = (instr >> 6) & 0b111;

            DEBUG_TRACE("VM_OPCODE_ADD dr %x sr %x\n", dr, sr1);

            if (instr & (1 << 5)) {
                vm_byte imm5 = sextend(instr, 5);
                vm->reg[dr] = vm->reg[sr1] + imm5;
            }
            else {
                vm_reg sr2 = instr & 0b111;
                vm->reg[dr] = vm->reg[sr1] + vm->reg[sr2];
            }

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_AND: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_reg sr1 = (instr >> 6) & 0b111;

            DEBUG_TRACE("VM_OPCODE_AND dr %x sr %x\n", dr, sr1);

            if (instr & (1 << 5)) {
                vm_byte imm5 = sextend(instr, 5);
                vm->reg[dr] = vm->reg[sr1] & imm5;
            }
            else {
                vm_reg sr2 = instr & 0b111;
                vm->reg[dr] = vm->reg[sr1] & vm->reg[sr2];
            }

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_BR: {
            vm_byte current_nzp = vm->reg[VM_REG_PSR] & 0b111;
            vm_byte desired_nzp = (instr >> 9) & 0b111;

            DEBUG_TRACE("VM_OPCODE_BR current_nzp %x desired_nzp %x\n", current_nzp, desired_nzp);

            if (current_nzp & desired_nzp) {
                vm_addr pc_offset9 = sextend(instr, 9);
                vm->reg[VM_REG_PC] += pc_offset9;
            }

            if (instr == 0)
                return VM_OPCODE_NOP;
            break;
        }

        case VM_OPCODE_JMP: {
            vm_reg baser = (instr >> 6) & 0b111;
 
            DEBUG_TRACE("VM_OPCODE_JMP %x %x\n", baser, instr);

            vm->reg[VM_REG_PC] = vm->reg[baser];
            break;
        }

        case VM_OPCODE_JSR: {
            if (instr & (1 << 11)) {
                vm->reg[7] = vm->reg[VM_REG_PC];
                vm_addr pc_offset11 = sextend(instr, 11);
                DEBUG_TRACE("VM_OPCODE_JSR pc_offset11 %x\n", pc_offset11);
                vm->reg[VM_REG_PC] += pc_offset11;
            }
            else {
                vm_reg baser = (instr >> 6) & 0b111;
                vm_reg tmp = vm->reg[baser];
                vm->reg[7] = vm->reg[VM_REG_PC];
                DEBUG_TRACE("VM_OPCODE_JSR baser %x val %x\n", baser, tmp);
                vm->reg[VM_REG_PC] = tmp;
            }

            break;
        }

        case VM_OPCODE_LD: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_addr pc_offset9 = sextend(instr, 9);

            DEBUG_TRACE("VM_OPCODE_LD dr %x pc_offset9 %x\n", dr, pc_offset9);

            vm->reg[dr] = vm_read(vm, vm->reg[VM_REG_PC] + pc_offset9);

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_LDI: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_addr pc_offset9 = sextend(instr, 9);

            DEBUG_TRACE("VM_OPCODE_LDI dr %x pc_offset9 %x\n", dr, pc_offset9);

            vm->reg[dr] = vm_read(vm, vm_read(vm, vm->reg[VM_REG_PC] + pc_offset9));

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_LDR: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_reg baser = (instr >> 6) & 0b111;
            vm_addr offset6 = sextend(instr, 6);

            DEBUG_TRACE("VM_OPCODE_LDR dr %x baser %x\n", dr, baser);

            vm->reg[dr] = vm_read(vm, vm->reg[baser] + offset6);

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_LEA: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_addr pc_offset9 = sextend(instr, 9);

            DEBUG_TRACE("VM_OPCODE_LEA dr %x pc_offset9 %x\n", dr, pc_offset9);

            vm->reg[dr] = vm->reg[VM_REG_PC] + pc_offset9;

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_NOT: {
            vm_reg dr = (instr >> 9) & 0b111;
            vm_reg sr = (instr >> 6) & 0b111;

            DEBUG_TRACE("VM_OPCODE_NOT dr %x sr %x\n", dr, sr);

            vm->reg[dr] = ~vm->reg[sr];

            vm_setcc(vm, dr);
            break;
        }

        case VM_OPCODE_RTI: {
            DEBUG_TRACE("VM_OPCODE_RTI\n");
            return VM_OPCODE_NOT_IMPLEMENTED;
        }

        case VM_OPCODE_ST: {
            vm_reg sr = (instr >> 9) & 0b111;
            vm_addr pc_offset9 = sextend(instr, 9);

            DEBUG_TRACE("VM_OPCODE_ST sr %x pc_offset9 %x\n", sr, pc_offset9);

            vm_write(vm, vm->reg[VM_REG_PC] + pc_offset9, vm->reg[sr]);

            break;
        }

        case VM_OPCODE_STI: {
            vm_reg sr = (instr >> 9) & 0b111;
            vm_addr pc_offset9 = sextend(instr, 9);

            DEBUG_TRACE("VM_OPCODE_STI sr %x pc_offset9 %x\n", sr, pc_offset9);

            vm_write(vm, vm_read(vm, vm->reg[VM_REG_PC] + pc_offset9), vm->reg[sr]);

            break;
        }

        case VM_OPCODE_STR: {
            vm_reg sr = (instr >> 9) & 0b111;
            vm_reg baser = (instr >> 6) & 0b111;
            vm_addr offset6 = sextend(instr, 6);

            DEBUG_TRACE("VM_OPCODE_STR sr %x baser %x\n", sr, baser);

            vm_write(vm, vm->reg[baser] + offset6, vm->reg[sr]);

            break;
        }

        case VM_OPCODE_TRAP: {
            vm_addr trapvect8 = instr & 0xff;

            DEBUG_TRACE("VM_OPCODE_TRAP trapvect8 %x\n", trapvect8);

            if (trapvect8 == 0x20) {
                // handle GETC efficiently to prevent high CPU usage when idle
                vm->reg[0] = getchar();
            }
            else {
                // fallback to OS implementation of remaining traps
                vm->reg[7] = vm->reg[VM_REG_PC];
                vm->reg[VM_REG_PC] = vm_read(vm, trapvect8);
            }

            break;
        }

        case VM_OPCODE_RESERVED:
            DEBUG_TRACE("VM_OPCODE_RESERVED\n");
            return VM_OPCODE_NOT_IMPLEMENTED;
    }

    return VM_SUCCESS;
}

vm_result vm_run(vm_ctx vm) {
    assert(vm != NULL);

    while (vm_read(vm, VM_ADDR_MCR) & VM_STATUS_BIT) {
        vm_result res = vm_perform(vm, vm_read(vm, vm->reg[VM_REG_PC]++));

        if (res != VM_SUCCESS) {
            return res;
        }
    }

    return VM_SUCCESS;
}
