// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once



#define INSTRUCTION_BIT_COUNT       16
#define OPER_CODE_BIT_COUNT         4
#define REG_NUM_BIT_COUNT           3

#define OPCODE_BR                   0b0000
#define OPCODE_ADD                  0b0001
#define OPCODE_LD                   0b0010
#define OPCODE_ST                   0b0011
#define OPCODE_JSR                  0b0100
#define OPCODE_AND                  0b0101
#define OPCODE_LDR                  0b0110
#define OPCODE_STR                  0b0111
#define OPCODE_RTI                  0b1000
#define OPCODE_NOT                  0b1001
#define OPCODE_LDI                  0b1010
#define OPCODE_STI                  0b1011
#define OPCODE_JMP                  0b1100
#define OPCODE_RES                  0b1101
#define OPCODE_LEA                  0b1110
#define OPCODE_TRAP                 0b1111

#define INT_VALUE(instr, bit_count) ((((instr) & ((1 << (bit_count)) - 1)) ^ (1 << ((bit_count) - 1))) - (1 << ((bit_count) - 1)))

#define OPER_CODE_MOVE_BIT          (INSTRUCTION_BIT_COUNT - OPER_CODE_BIT_COUNT)
#define OPER_CODE_MASK              ((1 << OPER_CODE_BIT_COUNT) - 1)
#define REG_NUM_MASK                ((1 << REG_NUM_BIT_COUNT) - 1)

#define OPER_CODE(instr)            ((instr >> OPER_CODE_MOVE_BIT) & OPER_CODE_MASK)

#define INT_AFTER_OPER_MASK         ((1 << OPER_CODE_MOVE_BIT) - 1)
#define INT_AFTER_OPER_WITH_FLAG_MASK ((1 << (OPER_CODE_MOVE_BIT - 1)) - 1)
#define INT_AFTER_OPER(instr)       INT_VALUE(instr, OPER_CODE_MOVE_BIT)
#define INT_AFTER_OPER_FLAG_BIT     (OPER_CODE_MOVE_BIT - 1)
#define INT_AFTER_OPER_FLAG(instr)  (instr & (1 << INT_AFTER_OPER_FLAG_BIT))
#define INT_AFTER_OPER_WITH_FLAG(instr) INT_VALUE(instr, OPER_CODE_MOVE_BIT - 1)

#define REG_NUM1_MOVE_BIT           (OPER_CODE_MOVE_BIT - REG_NUM_BIT_COUNT)
#define REG_NUM1_MASK               REG_NUM_MASK
#define REG_NUM1(instr)             ((instr >> REG_NUM1_MOVE_BIT) & REG_NUM1_MASK)

#define INT_AFTER_NUM1_MASK         ((1 << REG_NUM1_MOVE_BIT) - 1)
#define INT_AFTER_NUM1_WITH_FLAG_MASK ((1 << (REG_NUM1_MOVE_BIT - 1)) - 1)
#define INT_AFTER_NUM1(instr)       INT_VALUE(instr, REG_NUM1_MOVE_BIT)
#define INT_AFTER_NUM1_FLAG_BIT     (REG_NUM1_MOVE_BIT - 1)
#define INT_AFTER_NUM1_FLAG(instr)  (instr & (1 << INT_AFTER_NUM1_FLAG_BIT))
#define INT_AFTER_NUM1_WITH_FLAG(instr) INT_VALUE(instr, REG_NUM1_MOVE_BIT - 1)

#define REG_NUM2_MOVE_BIT           (REG_NUM1_MOVE_BIT - REG_NUM_BIT_COUNT)
#define REG_NUM2_MASK               REG_NUM_MASK
#define REG_NUM2(instr)             ((instr >> REG_NUM2_MOVE_BIT) & REG_NUM2_MASK)

#define REG_NUM3_MOVE_BIT           0
#define REG_NUM3_MASK               REG_NUM_MASK
#define REG_NUM3(instr)             ((instr >> REG_NUM3_MOVE_BIT) & REG_NUM3_MASK)

#define INT_AFTER_NUM2_MASK         ((1 << REG_NUM2_MOVE_BIT) - 1)
#define INT_AFTER_NUM2_WITH_FLAG_MASK ((1 << (REG_NUM2_MOVE_BIT - 1)) - 1)
#define INT_AFTER_NUM2(instr)       INT_VALUE(instr, REG_NUM2_MOVE_BIT)
#define INT_AFTER_NUM2_FLAG_BIT     (REG_NUM2_MOVE_BIT - 1)
#define INT_AFTER_NUM2_FLAG(instr)  (instr & (1 << INT_AFTER_NUM2_FLAG_BIT))
#define INT_AFTER_NUM2_WITH_FLAG(instr)  INT_VALUE(instr, REG_NUM2_MOVE_BIT - 1)

#define TRAP_MASK                   0xFF
