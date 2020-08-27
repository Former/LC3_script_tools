// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#include "instr_parser.h"
#include "instr_maker.h"
/*
#define OPCODE_BR                       0b0000
#define OPCODE_ADD                      0b0001
#define OPCODE_LD                       0b0010
#define OPCODE_ST                       0b0011
#define OPCODE_JSR                      0b0100
#define OPCODE_AND                      0b0101
#define OPCODE_LDR                      0b0110
#define OPCODE_STR                      0b0111
#define OPCODE_RTI                      0b1000
#define OPCODE_NOT                      0b1001
#define OPCODE_LDI                      0b1010
#define OPCODE_STI                      0b1011
#define OPCODE_JMP                      0b1100
#define OPCODE_RES                      0b1101
#define OPCODE_LEA                      0b1110
#define OPCODE_TRAP                     0b1111
*/

#define INT_VALUE_TO_SIGNED(val) (int(val))

#define LC3_CHECK_OPCODE_RI(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_BR) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_LD) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_ST) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_LDI) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_STI) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_LEA) \
            )

#define LC3_INSTR_CONVERT_RI(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            LC3_MAKE_INSTR_RI(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM1(instr, instr_bc_from, op_bc_from, rn_bc_from), INT_VALUE_TO_SIGNED(LC3_INT_AFTER_NUM1(instr, instr_bc_from, op_bc_from, rn_bc_from)), instr_bc_to, op_bc_to, rn_bc_to)

#define LC3_CHECK_OPCODE_RRR_RRI(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_ADD) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_AND) \
            )

#define LC3_INSTR_CONVERT_RRR_RRI(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            ( \
                LC3_INT_AFTER_NUM2_FLAG(instr, instr_bc_from, op_bc_from, rn_bc_from) ? \
                    LC3_MAKE_INSTR_RRI_WITH_FLAG(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM1(instr, instr_bc_from, op_bc_from, rn_bc_from), LC3_REG_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from), INT_VALUE_TO_SIGNED(LC3_INT_AFTER_NUM2_WITH_FLAG(instr, instr_bc_from, op_bc_from, rn_bc_from)), instr_bc_to, op_bc_to, rn_bc_to) \
                    : \
                    LC3_MAKE_INSTR_RRR(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM1(instr, instr_bc_from, op_bc_from, rn_bc_from), LC3_REG_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from), LC3_REG_NUM3(instr, rn_bc_from), instr_bc_to, op_bc_to, rn_bc_to) \
            )

#define LC3_CHECK_OPCODE_R2_I(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_JSR) \
            )

#define LC3_INSTR_CONVERT_R2_I(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            ( \
                LC3_INT_AFTER_OPER_FLAG(instr, instr_bc_from, op_bc_from) ? \
                    LC3_MAKE_INSTR_I_WITH_FLAG(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), INT_VALUE_TO_SIGNED(LC3_INT_AFTER_OPER_WITH_FLAG(instr, instr_bc_from, op_bc_from)), instr_bc_to, op_bc_to) \
                    : \
                    LC3_MAKE_INSTR_R2(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from), instr_bc_to, op_bc_to, rn_bc_to) \
            )

#define LC3_CHECK_OPCODE_RRI(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_LDR) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_STR) \
            )

#define LC3_INSTR_CONVERT_RRI(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            LC3_MAKE_INSTR_RRI(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM1(instr, instr_bc_from, op_bc_from, rn_bc_from), LC3_REG_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from), INT_VALUE_TO_SIGNED(LC3_INT_AFTER_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from)), instr_bc_to, op_bc_to, rn_bc_to)


#define LC3_INSTR_CONVERT(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            ( \
                (LC3_CHECK_OPCODE_RI(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_RI(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (LC3_CHECK_OPCODE_RRR_RRI(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_RRR_RRI(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (LC3_CHECK_OPCODE_R2_I(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_R2_I(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (LC3_CHECK_OPCODE_RRI(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_RRI(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (VALUE_ASSERT(((void)"This operation not implemented", LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), 0)), 0) \
            )

/*
#define LC3_MAKE_INSTR_RRR(opcode, reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_REGNUM(reg_num3, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (reg_num2 << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (reg_num3 << LC3_REG_NUM3_MOVE_BIT) \
    )

#define LC3_MAKE_INSTR_RRI(opcode, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_INT_AFTER_NUM2(int_val, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (reg_num2 << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (int_val & LC3_INT_AFTER_NUM2_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RRI_WITH_FLAG(opcode, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_INT_AFTER_NUM2_WITH_FLAG(int_val, instr_bc, op_bc, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (reg_num2 << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (1 << (LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)) | (int_val & LC3_INT_AFTER_NUM2_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RR(opcode, reg_num1, reg_num2, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (reg_num2 << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RI(opcode, reg_num1, int_val, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_INT_AFTER_NUM1(int_val, instr_bc, op_bc, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (int_val & LC3_INT_AFTER_NUM1_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RI_WITH_FLAG(opcode, reg_num1, int_val, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_INT_AFTER_NUM1_WITH_FLAG(int_val, instr_bc, op_bc, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (1 << (LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)) | (int_val & LC3_INT_AFTER_NUM1_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_R2(opcode, reg_num2, instr_bc, op_bc, rn_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (reg_num2 << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_I_WITH_FLAG(opcode, int_val, instr_bc, op_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_INT_AFTER_OPER_WITH_FLAG(int_val, instr_bc, op_bc), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (1 << LC3_INT_AFTER_OPER_FLAG_BIT(instr_bc, op_bc)) | (int_val & LC3_INT_AFTER_OPER_MASK(instr_bc, op_bc)) \
    )

#define LC3_MAKE_INSTR_T(opcode, int_val, instr_bc, op_bc) \
    (LC3_Sim::RegType)( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_INT_TRAP(int_val), \
    (opcode << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (int_val & LC3_TRAP_MASK) \
    )

*/
#if 0

#define LC3_MAKE_INSTR_LDR(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)     /* reg[reg_num1] = *(reg[reg_num2] + int_val); */ \
    LC3_MAKE_INSTR_RRI(OPCODE_LDR, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_STR(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)     /* *(reg[reg_num2] + int_val) = reg[reg_num1]; */ \
    LC3_MAKE_INSTR_RRI(OPCODE_STR, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_NOT(reg_num1, reg_num2, instr_bc, op_bc, rn_bc)              /* reg[reg_num1] = ~reg[reg_num2]; */ \
    LC3_MAKE_INSTR_RR(OPCODE_NOT, reg_num1, reg_num2, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_JMP(reg_num2, instr_bc, op_bc, rn_bc)                        /* reg_pc = reg[reg_num2]; */ \
    LC3_MAKE_INSTR_R2(OPCODE_JMP, reg_num2, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_TRAP(trap_val, instr_bc, op_bc)                              /* trap(trap_val); */ \
    LC3_MAKE_INSTR_T(OPCODE_TRAP, trap_val, instr_bc, op_bc)

#endif
