// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#ifdef __cplusplus
#include <cassert>
#else
//#include <assert>
#define assert(cond) ((void)0)
#endif

#define OPCODE_BR                       0b0000UL
#define OPCODE_ADD                      0b0001UL
#define OPCODE_LD                       0b0010UL
#define OPCODE_ST                       0b0011UL
#define OPCODE_JSR                      0b0100UL
#define OPCODE_AND                      0b0101UL
#define OPCODE_LDR                      0b0110UL
#define OPCODE_STR                      0b0111UL
#define OPCODE_RTI                      0b1000UL
#define OPCODE_NOT                      0b1001UL
#define OPCODE_LDI                      0b1010UL
#define OPCODE_STI                      0b1011UL
#define OPCODE_JMP                      0b1100UL
#define OPCODE_RES                      0b1101UL
#define OPCODE_LEA                      0b1110UL
#define OPCODE_TRAP                     0b1111UL

#define RES_OPCODE_SLL                  0
#define RES_OPCODE_SRA                  1
#define RES_OPCODE_DIV                  2
#define RES_OPCODE_MOD                  3
#define RES_OPCODE_MUL                  4
#define RES_OPCODE_SLLI                 5
#define RES_OPCODE_SRAI                 6

#define TO_OPER_TYPE(oper)              ((uint64_t)oper)

#define VALUE_ASSERT(cond) assert(cond) // TODO: Make static_assert

#define LC3_CHECK_OPCODE(opcode, op_bc) \
    VALUE_ASSERT(!(opcode & ~LC3_OPER_CODE_MASK(op_bc)))

#define LC3_CHECK_REGNUM(reg_num, rn_bc) \
    VALUE_ASSERT(!(reg_num & ~LC3_REG_NUM_MASK(rn_bc)))

#define LC3_CHECK_INT_WITH_MASK(int_val, mask) \
    VALUE_ASSERT(!( (((int_val) < 0) ? (-int_val) : (int_val)) & ~mask))

#define LC3_CHECK_INT_AFTER_OPER_WITH_FLAG(int_val, instr_bc, op_bc) \
    LC3_CHECK_INT_WITH_MASK(int_val, LC3_INT_AFTER_OPER_WITH_FLAG_MASK(instr_bc, op_bc))

#define LC3_CHECK_INT_AFTER_NUM1(int_val, instr_bc, op_bc, rn_bc) \
    LC3_CHECK_INT_WITH_MASK(int_val, LC3_INT_AFTER_NUM1_MASK(instr_bc, op_bc, rn_bc))

#define LC3_CHECK_INT_AFTER_NUM1_WITH_FLAG(int_val, instr_bc, op_bc, rn_bc) \
    LC3_CHECK_INT_WITH_MASK(int_val, LC3_INT_AFTER_NUM1_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc))

#define LC3_CHECK_INT_AFTER_NUM2(int_val, instr_bc, op_bc, rn_bc) \
    LC3_CHECK_INT_WITH_MASK(int_val, LC3_INT_AFTER_NUM2_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc))

#define LC3_CHECK_INT_AFTER_NUM2_WITH_FLAG(int_val, instr_bc, op_bc, rn_bc) \
    LC3_CHECK_INT_WITH_MASK(int_val, LC3_INT_AFTER_NUM2_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc))

#define LC3_CHECK_INT_TRAP(int_val, instr_bc, op_bc) \
    VALUE_ASSERT(!(TO_OPER_TYPE(int_val) & ~LC3_TRAP_MASK(instr_bc, op_bc)))

#define LC3_CHECK_PARAM(par_val, par_bc) \
    LC3_CHECK_INT_WITH_MASK(par_val, LC3_PARAM_AFTER_NUM2_MASK(par_bc))

#define LC3_CHECK_UINT_AFTER_PARAM(int_val, instr_bc, op_bc, rn_bc, par_bc) \
    LC3_CHECK_INT_WITH_MASK(int_val, LC3_UINT_AFTER_PARAM_MASK(instr_bc, op_bc, rn_bc, par_bc))


#define LC3_MAKE_INSTR_RRR(opcode, reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_REGNUM(reg_num3, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num3) << LC3_REG_NUM3_MOVE_BIT) \
    )

#define LC3_MAKE_INSTR_RRI(opcode, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_INT_AFTER_NUM2(int_val, instr_bc, op_bc, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(int_val) & LC3_INT_AFTER_NUM2_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RRPI(opcode, reg_num1, reg_num2, par_val, int_val, instr_bc, op_bc, rn_bc, par_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_PARAM(par_val, par_bc), LC3_CHECK_UINT_AFTER_PARAM(int_val, instr_bc, op_bc, rn_bc, par_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(par_val) << LC3_PARAM_AFTER_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc, par_bc)) | (TO_OPER_TYPE(int_val) & LC3_UINT_AFTER_PARAM_MASK(instr_bc, op_bc, rn_bc, par_bc)) \
    )

#define LC3_MAKE_INSTR_RRI_WITH_FLAG(opcode, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_INT_AFTER_NUM2_WITH_FLAG(int_val, instr_bc, op_bc, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(1) << (LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)) | (TO_OPER_TYPE(int_val) & LC3_INT_AFTER_NUM2_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RR(opcode, reg_num1, reg_num2, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RI(opcode, reg_num1, int_val, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_INT_AFTER_NUM1(int_val, instr_bc, op_bc, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(int_val) & LC3_INT_AFTER_NUM1_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_RI_WITH_FLAG(opcode, reg_num1, int_val, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_INT_AFTER_NUM1_WITH_FLAG(int_val, instr_bc, op_bc, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(1) << (LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)) | (TO_OPER_TYPE(int_val) & LC3_INT_AFTER_NUM1_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_R2(opcode, reg_num2, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) \
    )

#define LC3_MAKE_INSTR_I_WITH_FLAG(opcode, int_val, instr_bc, op_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_INT_AFTER_OPER_WITH_FLAG(int_val, instr_bc, op_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(1) << LC3_INT_AFTER_OPER_FLAG_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(int_val) & LC3_INT_AFTER_OPER_MASK(instr_bc, op_bc)) \
    )

#define LC3_MAKE_INSTR_T(opcode, int_val, instr_bc, op_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_INT_TRAP(int_val, instr_bc, op_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(int_val) & LC3_TRAP_MASK(instr_bc, op_bc)) \
    )

#define LC3_MAKE_INSTR_NOP(instr_bc, op_bc, rn_bc)                                  /* Not operation */ \
    LC3_MAKE_INSTR_BR(0, 0, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_BR(flag_pzn, int_val, instr_bc, op_bc, rn_bc)                /* if (cur_pzn == flag_pzn) reg_pc += int_val; */ \
    LC3_MAKE_INSTR_RI(OPCODE_BR, flag_pzn, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_ADD_I(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)   /* reg[reg_num1] = reg[reg_num2] + int_val; */ \
    LC3_MAKE_INSTR_RRI_WITH_FLAG(OPCODE_ADD, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_ADD_R(reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc)  /* reg[reg_num1] = reg[reg_num2] + reg[reg_num3]; */ \
    LC3_MAKE_INSTR_RRR(OPCODE_ADD, reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_LD(reg_num1, int_val, instr_bc, op_bc, rn_bc)                /* reg[reg_num1] = *(reg_pc + int_val); */ \
    LC3_MAKE_INSTR_RI(OPCODE_LD, reg_num1, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_ST(reg_num1, int_val, instr_bc, op_bc, rn_bc)                /* *(reg_pc + int_val) = reg[reg_num1]; */ \
    LC3_MAKE_INSTR_RI(OPCODE_ST, reg_num1, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_JSR_I(int_val, instr_bc, op_bc)                              /* reg[7] = reg_pc; reg_pc += int_val; */ \
    LC3_MAKE_INSTR_I_WITH_FLAG(OPCODE_JSR, int_val, instr_bc, op_bc)

#define LC3_MAKE_INSTR_JSR_R(reg_num2, instr_bc, op_bc, rn_bc)                      /* swap(&reg[reg_num2], &reg_pc); */ \
    LC3_MAKE_INSTR_R2(OPCODE_JSR, reg_num2, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_AND_I(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)   /* reg[reg_num1] = reg[reg_num2] & int_val; */ \
    LC3_MAKE_INSTR_RRI_WITH_FLAG(OPCODE_AND, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_AND_R(reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc)  /* reg[reg_num1] = reg[reg_num2] & reg[reg_num3]; */ \
    LC3_MAKE_INSTR_RRR(OPCODE_AND, reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_LDR(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)     /* reg[reg_num1] = *(reg[reg_num2] + int_val); */ \
    LC3_MAKE_INSTR_RRI(OPCODE_LDR, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_STR(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)     /* *(reg[reg_num2] + int_val) = reg[reg_num1]; */ \
    LC3_MAKE_INSTR_RRI(OPCODE_STR, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_NOT(reg_num1, reg_num2, instr_bc, op_bc, rn_bc)              /* reg[reg_num1] = ~reg[reg_num2]; */ \
    LC3_MAKE_INSTR_RR(OPCODE_NOT, reg_num1, reg_num2, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_LDI(reg_num1, int_val, instr_bc, op_bc, rn_bc)               /* reg[reg_num1] = *(*(reg_pc + int_val)); */ \
    LC3_MAKE_INSTR_RI(OPCODE_LDI, reg_num1, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_STI(reg_num1, int_val, instr_bc, op_bc, rn_bc)               /* *(*(reg_pc + int_val)) = reg[reg_num1]; */ \
    LC3_MAKE_INSTR_RI(OPCODE_STI, reg_num1, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_JMP(reg_num2, instr_bc, op_bc, rn_bc)                        /* reg_pc = reg[reg_num2]; */ \
    LC3_MAKE_INSTR_R2(OPCODE_JMP, reg_num2, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_LEA(reg_num1, int_val, instr_bc, op_bc, rn_bc)               /* reg[reg_num1] = reg_pc + int_val; */ \
    LC3_MAKE_INSTR_RI(OPCODE_LEA, reg_num1, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_TRAP(trap_val, instr_bc, op_bc)                              /* trap(trap_val); */ \
    LC3_MAKE_INSTR_T(OPCODE_TRAP, trap_val, instr_bc, op_bc)

#define LC3_MAKE_INSTR_RTI(reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)     /* RTI(reg[reg_num1], reg[reg_num2], int_val); */ \
    LC3_MAKE_INSTR_RRI(OPCODE_RTI, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc)

#define LC3_MAKE_INSTR_RES(reg_num1, reg_num2, par_val, int_val_or_reg_num3, instr_bc, op_bc, rn_bc, par_bc)  /* RES(reg[reg_num1], reg[reg_num2], par_val, int_val); */ \
    LC3_MAKE_INSTR_RRPI(OPCODE_RES, reg_num1, reg_num2, par_val, int_val_or_reg_num3, instr_bc, op_bc, rn_bc, par_bc)


