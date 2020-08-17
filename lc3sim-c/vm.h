//
//  Created by Ryan Pendleton on 6/28/18.
//  Copyright © 2018 Ryan Pendleton. All rights reserved.
//  Changed 16.08.2020 Alexei Bezborodov
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "types.h"

typedef struct vm_impl* vm_ctx;

typedef lc3_register_type vm_byte;
typedef lc3_mem_addres_type vm_addr;

typedef enum {
    VM_LOAD_SUCCESS,
    VM_INPUT_NOT_FOUND,
    VM_INPUT_TOO_LARGE,
} vm_load_result;

typedef enum {
    // Success
    VM_SUCCESS,
    VM_OPCODE_NOP,
    VM_RES_ADDR_MCR,
    // Errors
    VM_OPCODE_NOT_IMPLEMENTED,
    VM_ERROR_ADDRES_OUT_OF_RANGE,
} vm_result;

vm_ctx vm_create(void);
void vm_destroy(vm_ctx vm);

vm_load_result vm_load_os(vm_ctx vm);
vm_load_result vm_load_file(vm_ctx vm, const char *file);
vm_load_result vm_load_data(vm_ctx vm, unsigned const char *data, size_t length);

vm_result vm_mem_read(vm_ctx vm, vm_addr addr, vm_byte* out);

vm_result vm_run(vm_ctx vm);

#ifdef __cplusplus
}
#endif
