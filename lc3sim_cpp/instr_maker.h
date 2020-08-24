// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#include <cassert>

#include "instr_config.h"

#define VALUE_ASSERT(cond) assert(cond) // TODO Make static_assert
#define CHECK_OPCODE(opcode) VALUE_ASSERT(!(opcode & ~OPER_CODE_MASK))
#define CHECK_REGNUM(reg_num) VALUE_ASSERT(!(reg_num & ~REG_NUM_MASK))
#define CHECK_INT_AFTER_OPER_WITH_FLAG(int_val) VALUE_ASSERT(!(int_val & ~INT_AFTER_OPER_WITH_FLAG_MASK))
#define CHECK_INT_AFTER_NUM1(int_val) VALUE_ASSERT(!(int_val & ~INT_AFTER_NUM1_MASK))
#define CHECK_INT_AFTER_NUM2(int_val) VALUE_ASSERT(!(int_val & ~INT_AFTER_NUM2_MASK))
#define CHECK_INT_AFTER_NUM1_WITH_FLAG(int_val) VALUE_ASSERT(!(int_val & ~INT_AFTER_NUM1_WITH_FLAG_MASK))
#define CHECK_INT_AFTER_NUM2_WITH_FLAG(int_val) VALUE_ASSERT(!(int_val & ~INT_AFTER_NUM2_WITH_FLAG_MASK))
#define CHECK_INT_TRAP(int_val) VALUE_ASSERT(!(int_val & ~TRAP_MASK))

#define MAKE_INSTR_RRR(opcode, reg_num1, reg_num2, reg_num3) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num1), CHECK_REGNUM(reg_num2), CHECK_REGNUM(reg_num3), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num1 << REG_NUM1_MOVE_BIT) | (reg_num2 << REG_NUM2_MOVE_BIT) | (reg_num3 << REG_NUM3_MOVE_BIT) \
    )

#define MAKE_INSTR_RRI(opcode, reg_num1, reg_num2, int_val) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num1), CHECK_REGNUM(reg_num2), CHECK_INT_AFTER_NUM2(int_val), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num1 << REG_NUM1_MOVE_BIT) | (reg_num2 << REG_NUM2_MOVE_BIT) | int_val \
    )

#define MAKE_INSTR_RRI_WITH_FLAG(opcode, reg_num1, reg_num2, int_val) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num1), CHECK_REGNUM(reg_num2), CHECK_INT_AFTER_NUM2_WITH_FLAG(int_val), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num1 << REG_NUM1_MOVE_BIT) | (reg_num2 << REG_NUM2_MOVE_BIT) | (1 << (REG_NUM2_MOVE_BIT - 1)) | int_val \
    )

#define MAKE_INSTR_RR(opcode, reg_num1, reg_num2) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num1), CHECK_REGNUM(reg_num2), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num1 << REG_NUM1_MOVE_BIT) | (reg_num2 << REG_NUM2_MOVE_BIT) \
    )

#define MAKE_INSTR_RI(opcode, reg_num1, int_val) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num1), CHECK_INT_AFTER_NUM1(int_val), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num1 << REG_NUM1_MOVE_BIT) | int_val \
    )

#define MAKE_INSTR_RI_WITH_FLAG(opcode, reg_num1, int_val) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num1), CHECK_INT_AFTER_NUM1_WITH_FLAG(int_val), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num1 << REG_NUM1_MOVE_BIT) | (1 << (REG_NUM1_MOVE_BIT - 1)) | int_val \
    )

#define MAKE_INSTR_R2(opcode, reg_num2) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_REGNUM(reg_num2), \
    (opcode << OPER_CODE_MOVE_BIT) | (reg_num2 << REG_NUM2_MOVE_BIT) \
    )

#define MAKE_INSTR_I_WITH_FLAG(opcode, int_val) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_INT_AFTER_OPER_WITH_FLAG(int_val), \
    (opcode << OPER_CODE_MOVE_BIT) | (1 << INT_AFTER_OPER_FLAG_BIT) | int_val \
    )

#define MAKE_INSTR_T(opcode, int_val) \
    (LC3_Sim::RegType)( CHECK_OPCODE(opcode), CHECK_INT_TRAP(int_val), \
    (opcode << OPER_CODE_MOVE_BIT) | int_val \
    )

#define MAKE_INSTR_BR(flag_pzn, int_val)                /* if (cur_pzn == flag_pzn) reg_pc += int_val; */ \
    MAKE_INSTR_RI(OPCODE_BR, flag_pzn, int_val)

#define MAKE_INSTR_ADD_I(reg_num1, reg_num2, int_val)   /* reg[reg_num1] = reg[reg_num2] + int_val; */ \
    MAKE_INSTR_RRI_WITH_FLAG(OPCODE_ADD, reg_num1, reg_num2, int_val)

#define MAKE_INSTR_ADD_R(reg_num1, reg_num2, reg_num3)  /* reg[reg_num1] = reg[reg_num2] + reg[reg_num3]; */ \
    MAKE_INSTR_RRR(OPCODE_ADD, reg_num1, reg_num2, reg_num3)

#define MAKE_INSTR_LD(reg_num1, int_val)                /* reg[reg_num1] = *(reg_pc + int_val); */ \
    MAKE_INSTR_RI(OPCODE_LD, reg_num1, int_val)

#define MAKE_INSTR_ST(reg_num1, int_val)                /* *(reg_pc + int_val) = reg[reg_num1]; */ \
    MAKE_INSTR_RI(OPCODE_ST, reg_num1, int_val)

#define MAKE_INSTR_JSR_I(int_val)                       /* reg[7] = reg_pc; reg_pc += int_val; */ \
    MAKE_INSTR_I_WITH_FLAG(OPCODE_JSR, int_val)

#define MAKE_INSTR_JSR_R(reg_num2)                      /* swap(reg[reg_num2], reg_pc); */ \
    MAKE_INSTR_R2(OPCODE_JMP, reg_num2)

#define MAKE_INSTR_AND_I(reg_num1, reg_num2, int_val)   /* reg[reg_num1] = reg[reg_num2] & int_val; */ \
    MAKE_INSTR_RRI_WITH_FLAG(OPCODE_AND, reg_num1, reg_num2, int_val)

#define MAKE_INSTR_AND_R(reg_num1, reg_num2, reg_num3)  /* reg[reg_num1] = reg[reg_num2] & reg[reg_num3]; */ \
    MAKE_INSTR_RRR(OPCODE_AND, reg_num1, reg_num2, reg_num3)

#define MAKE_INSTR_LDR(reg_num1, reg_num2, int_val)     /* reg[reg_num1] = *(reg[reg_num2] + int_val); */ \
    MAKE_INSTR_RRI(OPCODE_LDR, reg_num1, reg_num2, int_val)

#define MAKE_INSTR_STR(reg_num1, reg_num2, int_val)     /* *(reg[reg_num2] + int_val) = reg[reg_num1]; */ \
    MAKE_INSTR_RRI(OPCODE_STR, reg_num1, reg_num2, int_val)

#define MAKE_INSTR_NOT(reg_num1, reg_num2)              /* reg[reg_num1] = ~reg[reg_num2]; */ \
    MAKE_INSTR_RR(OPCODE_NOT, reg_num1, reg_num2)

#define MAKE_INSTR_LDI(reg_num1, int_val)               /* reg[reg_num1] = *(*(reg_pc + int_val)); */ \
    MAKE_INSTR_RI(OPCODE_LDI, reg_num1, int_val)

#define MAKE_INSTR_STI(reg_num1, int_val)               /* *(*(reg_pc + int_val)) = reg[reg_num1]; */ \
    MAKE_INSTR_RI(OPCODE_STI, reg_num1, int_val)

#define MAKE_INSTR_JMP(reg_num2)                        /* reg_pc = reg[reg_num2]; */ \
    MAKE_INSTR_R2(OPCODE_JMP, reg_num2)

#define MAKE_INSTR_LEA(reg_num1, int_val)               /* reg[reg_num1] = reg_pc + int_val; */ \
    MAKE_INSTR_RI(OPCODE_LEA, reg_num1, int_val)

#define MAKE_INSTR_TRAP(trap_val)                       /* trap(trap_val); */ \
    MAKE_INSTR_T(OPCODE_TRAP, trap_val)



