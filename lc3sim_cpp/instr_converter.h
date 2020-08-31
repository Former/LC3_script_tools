// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#include "instr_parser.h"
#include "instr_maker.h"

#define INT_VALUE_TO_SIGNED(val) ((int64_t)(val))

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


#define LC3_CHECK_OPCODE_RR(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_NOT) \
            )

#define LC3_INSTR_CONVERT_RR(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            LC3_MAKE_INSTR_RR(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM1(instr, instr_bc_from, op_bc_from, rn_bc_from), LC3_REG_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from), instr_bc_to, op_bc_to, rn_bc_to)

#define LC3_CHECK_OPCODE_R2(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_JMP) \
            )

#define LC3_INSTR_CONVERT_R2(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            LC3_MAKE_INSTR_R2(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_REG_NUM2(instr, instr_bc_from, op_bc_from, rn_bc_from), instr_bc_to, op_bc_to, rn_bc_to)


#define LC3_CHECK_OPCODE_T(instr, instr_bc, op_bc) \
            ( \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_RTI) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_RES) || \
                (LC3_OPER_CODE(instr, instr_bc, op_bc) == OPCODE_TRAP) \
            )

#define LC3_INSTR_CONVERT_T(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
            LC3_MAKE_INSTR_T(LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), LC3_TRAP(instr, instr_bc_from, op_bc_from), instr_bc_to, op_bc_to)


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
                (LC3_CHECK_OPCODE_RR(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_RR(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (LC3_CHECK_OPCODE_R2(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_R2(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (LC3_CHECK_OPCODE_T(instr, instr_bc_from, op_bc_from)) ? \
                    LC3_INSTR_CONVERT_T(instr, instr_bc_from, op_bc_from, rn_bc_from, instr_bc_to, op_bc_to, rn_bc_to) \
                : \
                (VALUE_ASSERT(((void)"This operation not implemented", (void)LC3_OPER_CODE(instr, instr_bc_from, op_bc_from), 0)), 0) \
            )
