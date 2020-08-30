// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#define I1                      (1UL)

#define INT_VALUE(instr, bit_count) \
                                ((((instr) & ((I1 << (bit_count)) - 1)) ^ (I1 << ((bit_count) - 1))) - (I1 << ((bit_count) - 1)))

#define LC3_OPER_CODE_MOVE_BIT(instr_bit_count, oper_bit_count) \
                                (instr_bit_count - oper_bit_count)
#define LC3_OPER_CODE_MASK(oper_bit_count) \
                                ((I1 << oper_bit_count) - 1)
#define LC3_REG_NUM_MASK(reg_num_bit_count) \
                                ((I1 << reg_num_bit_count) - 1)

#define LC3_OPER_CODE(instr, instr_bc, op_bc) \
                                ((instr >> LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) & LC3_OPER_CODE_MASK(op_bc))

#define LC3_INT_AFTER_OPER_MASK(instr_bc, op_bc) \
                                ((I1 << LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc)) - 1)
#define LC3_INT_AFTER_OPER_WITH_FLAG_MASK(instr_bc, op_bc) \
                                ((I1 << (LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc) - 1)) - 1)
#define LC3_INT_AFTER_OPER(instr, instr_bc, op_bc) \
                                INT_VALUE(instr, LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc))
#define LC3_INT_AFTER_OPER_FLAG_BIT(instr_bc, op_bc) \
                                (LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc) - 1)
#define LC3_INT_AFTER_OPER_FLAG(instr, instr_bc, op_bc) \
                                (instr & (I1 << LC3_INT_AFTER_OPER_FLAG_BIT(instr_bc, op_bc)))
#define LC3_INT_AFTER_OPER_WITH_FLAG(instr, instr_bc, op_bc) \
                                INT_VALUE(instr, LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc) - 1)

#define LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) \
                                (LC3_OPER_CODE_MOVE_BIT(instr_bc, op_bc) - rn_bc)
#define LC3_REG_NUM1_MASK(rn_bc) \
                                LC3_REG_NUM_MASK(rn_bc)
#define LC3_REG_NUM1(instr, instr_bc, op_bc, rn_bc) \
                                ((instr >> LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) & LC3_REG_NUM1_MASK(rn_bc))

#define LC3_INT_AFTER_NUM1_MASK(instr_bc, op_bc, rn_bc) \
                                ((I1 << LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc)) - 1)
#define LC3_INT_AFTER_NUM1_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc) \
                                ((I1 << (LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)) - 1)
#define LC3_INT_AFTER_NUM1(instr, instr_bc, op_bc, rn_bc) \
                                INT_VALUE(instr, LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc))
#define LC3_INT_AFTER_NUM1_FLAG_BIT(instr_bc, op_bc, rn_bc) \
                                (LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)
#define LC3_INT_AFTER_NUM1_FLAG(instr, instr_bc, op_bc, rn_bc) \
                                (instr & (I1 << LC3_INT_AFTER_NUM1_FLAG_BIT(instr_bc, op_bc, rn_bc)))
#define LC3_INT_AFTER_NUM1_WITH_FLAG(instr, instr_bc, op_bc, rn_bc) \
                                INT_VALUE(instr, LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)

#define LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc) \
                                (LC3_REG_NUM1_MOVE_BIT(instr_bc, op_bc, rn_bc) - rn_bc)
#define LC3_REG_NUM2_MASK(rn_bc) \
                                LC3_REG_NUM_MASK(rn_bc)
#define LC3_REG_NUM2(instr, instr_bc, op_bc, rn_bc) \
                                ((instr >> LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) & LC3_REG_NUM2_MASK(rn_bc))

#define LC3_REG_NUM3_MOVE_BIT \
                                0
#define LC3_REG_NUM3_MASK(rn_bc) \
                                LC3_REG_NUM_MASK(rn_bc)
#define LC3_REG_NUM3(instr, rn_bc) \
                                ((instr >> LC3_REG_NUM3_MOVE_BIT) & LC3_REG_NUM3_MASK(rn_bc))

#define LC3_INT_AFTER_NUM2_MASK(instr_bc, op_bc, rn_bc) \
                                ((I1 << LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc)) - 1)
#define LC3_INT_AFTER_NUM2_WITH_FLAG_MASK(instr_bc, op_bc, rn_bc) \
                                ((I1 << (LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)) - 1)
#define LC3_INT_AFTER_NUM2(instr, instr_bc, op_bc, rn_bc) \
                                INT_VALUE(instr, LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc))
#define LC3_INT_AFTER_NUM2_FLAG_BIT(instr_bc, op_bc, rn_bc) \
                                (LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)
#define LC3_INT_AFTER_NUM2_FLAG(instr, instr_bc, op_bc, rn_bc) \
                                (instr & (I1 << LC3_INT_AFTER_NUM2_FLAG_BIT(instr_bc, op_bc, rn_bc)))
#define LC3_INT_AFTER_NUM2_WITH_FLAG(instr, instr_bc, op_bc, rn_bc) \
                                INT_VALUE(instr, LC3_REG_NUM2_MOVE_BIT(instr_bc, op_bc, rn_bc) - 1)

#define LC3_TRAP_MASK(instr_bc, op_bc) \
                                LC3_INT_AFTER_OPER_MASK(instr_bc, op_bc)

#define LC3_TRAP(instr, instr_bc, op_bc) \
                                LC3_INT_AFTER_OPER(instr, instr_bc, op_bc)
