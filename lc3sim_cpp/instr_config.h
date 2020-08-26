// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#include "sim_types.h"
#include "instr_parser.h"
#include "instr_maker.h"

#define INSTRUCTION_BIT_COUNT           LC3_INSTRUCTION_BIT_COUNT
#define OPER_CODE_BIT_COUNT             4
#define REG_NUM_BIT_COUNT               3

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

#define OPER_CODE_MOVE_BIT              LC3_OPER_CODE_MOVE_BIT(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define OPER_CODE_MASK                  LC3_OPER_CODE_MASK(OPER_CODE_BIT_COUNT)
#define REG_NUM_MASK                    LC3_REG_NUM_MASK(REG_NUM_BIT_COUNT)

#define OPER_CODE(instr)                LC3_OPER_CODE(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)

#define INT_AFTER_OPER_MASK             LC3_INT_AFTER_OPER_MASK(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define INT_AFTER_OPER_WITH_FLAG_MASK   LC3_INT_AFTER_OPER_WITH_FLAG_MASK(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define INT_AFTER_OPER(instr)           LC3_INT_AFTER_OPER(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define INT_AFTER_OPER_FLAG_BIT         LC3_INT_AFTER_OPER_FLAG_BIT(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define INT_AFTER_OPER_FLAG(instr)      LC3_INT_AFTER_OPER_FLAG(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define INT_AFTER_OPER_WITH_FLAG(instr) LC3_INT_AFTER_OPER_WITH_FLAG(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)

#define REG_NUM1_MOVE_BIT               LC3_REG_NUM1_MOVE_BIT(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define REG_NUM1_MASK                   LC3_REG_NUM1_MASK(REG_NUM_BIT_COUNT)
#define REG_NUM1(instr)                 LC3_REG_NUM1(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)

#define INT_AFTER_NUM1_MASK             LC3_INT_AFTER_NUM1_MASK(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM1_WITH_FLAG_MASK   LC3_INT_AFTER_NUM1_WITH_FLAG_MASK(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM1(instr)           LC3_INT_AFTER_NUM1(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM1_FLAG_BIT         LC3_INT_AFTER_NUM1_FLAG_BIT(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM1_FLAG(instr)      LC3_INT_AFTER_NUM1_FLAG(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM1_WITH_FLAG(instr) LC3_INT_AFTER_NUM1_WITH_FLAG(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)

#define REG_NUM2_MOVE_BIT               LC3_REG_NUM2_MOVE_BIT(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define REG_NUM2_MASK                   LC3_REG_NUM2_MASK(REG_NUM_BIT_COUNT)
#define REG_NUM2(instr)                 LC3_REG_NUM2(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)

#define REG_NUM3_MOVE_BIT               LC3_REG_NUM3_MOVE_BIT
#define REG_NUM3_MASK                   LC3_REG_NUM3_MASK(REG_NUM_BIT_COUNT)
#define REG_NUM3(instr)                 LC3_REG_NUM3(instr, REG_NUM_BIT_COUNT)

#define INT_AFTER_NUM2_MASK             LC3_INT_AFTER_NUM2_MASK(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM2_WITH_FLAG_MASK   LC3_INT_AFTER_NUM2_WITH_FLAG_MASK(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM2(instr)           LC3_INT_AFTER_NUM2(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM2_FLAG_BIT         LC3_INT_AFTER_NUM2_FLAG_BIT(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM2_FLAG(instr)      LC3_INT_AFTER_NUM2_FLAG(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define INT_AFTER_NUM2_WITH_FLAG(instr) LC3_INT_AFTER_NUM2_WITH_FLAG(instr, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)

#define TRAP_MASK                       LC3_TRAP_MASK


#define MAKE_INSTR_NOP \
                                        LC3_MAKE_INSTR_NOP(INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_BR(flag_pzn, int_val) \
                                        LC3_MAKE_INSTR_BR(flag_pzn, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_ADD_I(reg_num1, reg_num2, int_val) \
                                        LC3_MAKE_INSTR_ADD_I(reg_num1, reg_num2, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_ADD_R(reg_num1, reg_num2, reg_num3) \
                                        LC3_MAKE_INSTR_ADD_R(reg_num1, reg_num2, reg_num3, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_LD(reg_num1, int_val) \
                                        LC3_MAKE_INSTR_LD(reg_num1, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_ST(reg_num1, int_val) \
                                        LC3_MAKE_INSTR_ST(reg_num1, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_JSR_I(int_val) \
                                        LC3_MAKE_INSTR_JSR_I(int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
#define MAKE_INSTR_JSR_R(reg_num2) \
                                        LC3_MAKE_INSTR_JSR_R(reg_num2, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_AND_I(reg_num1, reg_num2, int_val) \
                                        LC3_MAKE_INSTR_AND_I(reg_num1, reg_num2, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_AND_R(reg_num1, reg_num2, reg_num3) \
                                        LC3_MAKE_INSTR_AND_R(reg_num1, reg_num2, reg_num3, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_LDR(reg_num1, reg_num2, int_val) \
                                        LC3_MAKE_INSTR_LDR(reg_num1, reg_num2, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_STR(reg_num1, reg_num2, int_val) \
                                        LC3_MAKE_INSTR_STR(reg_num1, reg_num2, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_NOT(reg_num1, reg_num2) \
                                        LC3_MAKE_INSTR_NOT(reg_num1, reg_num2, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_LDI(reg_num1, int_val) \
                                        LC3_MAKE_INSTR_LDI(reg_num1, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_STI(reg_num1, int_val) \
                                        LC3_MAKE_INSTR_STI(reg_num1, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_JMP(reg_num2) \
                                        LC3_MAKE_INSTR_JMP(reg_num2, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_LEA(reg_num1, int_val) \
                                        LC3_MAKE_INSTR_LEA(reg_num1, int_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT, REG_NUM_BIT_COUNT)
#define MAKE_INSTR_TRAP(trap_val) \
                                        LC3_MAKE_INSTR_TRAP(trap_val, INSTRUCTION_BIT_COUNT, OPER_CODE_BIT_COUNT)
