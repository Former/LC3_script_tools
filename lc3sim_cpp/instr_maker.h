// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#ifdef __cplusplus
#include <cassert>
#else
//#include <assert>
#define assert(cond) ((void)0)
#endif

#define OPCODE_BR                       ((uint64_t)0b0000)
#define OPCODE_ADD                      ((uint64_t)0b0001)
#define OPCODE_LD                       ((uint64_t)0b0010)
#define OPCODE_ST                       ((uint64_t)0b0011)
#define OPCODE_JSR                      ((uint64_t)0b0100)
#define OPCODE_AND                      ((uint64_t)0b0101)
#define OPCODE_LDR                      ((uint64_t)0b0110)
#define OPCODE_STR                      ((uint64_t)0b0111)
#define OPCODE_RTI                      ((uint64_t)0b1000)
#define OPCODE_NOT                      ((uint64_t)0b1001)
#define OPCODE_LDI                      ((uint64_t)0b1010)
#define OPCODE_STI                      ((uint64_t)0b1011)
#define OPCODE_JMP                      ((uint64_t)0b1100)
#define OPCODE_RES                      ((uint64_t)0b1101)
#define OPCODE_LEA                      ((uint64_t)0b1110)
#define OPCODE_TRAP                     ((uint64_t)0b1111)

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


#define LC3_MAKE_INSTR_RRR(opcode, reg_num1, reg_num2, reg_num3, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_REGNUM(reg_num3, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num3) << LC3_REG_NUM3_MOVE_BIT) \
    )

#define LC3_MAKE_INSTR_RRI(opcode, reg_num1, reg_num2, int_val, instr_bc, op_bc, rn_bc) \
    ( LC3_CHECK_OPCODE(opcode, op_bc), LC3_CHECK_REGNUM(reg_num1, rn_bc), LC3_CHECK_REGNUM(reg_num2, rn_bc), LC3_CHECK_INT_AFTER_NUM2(int_val, instr_bc, op_bc, rn_bc), \
    (TO_OPER_TYPE(opcode) << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) | (TO_OPER_TYPE(reg_num1) << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(reg_num2) << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) | (TO_OPER_TYPE(int_val) & LC3_INT_AFTER_NUM2_MASK(instr_bc, op_bc, rn_bc)) \
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

#define LC3_MAKE_INSTR_RTI(val, instr_bc, op_bc)                                    /* RTI(val); */ \
    LC3_MAKE_INSTR_T(OPCODE_RTI, val, instr_bc, op_bc)

#define LC3_MAKE_INSTR_RES(val, instr_bc, op_bc)                                    /* RES(val); */ \
    LC3_MAKE_INSTR_T(OPCODE_RES, val, instr_bc, op_bc)


