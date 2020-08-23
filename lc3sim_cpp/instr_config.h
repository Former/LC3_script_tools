// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#pragma once

#define INSTRUCTION_BIT_COUNT       16
#define OPER_CODE_BIT_COUNT         4
#define REG_NUM_BIT_COUNT           3

#define OPER_CODE_MOVE_BIT          (INSTRUCTION_BIT_COUNT - OPER_CODE_BIT_COUNT)
#define OPER_CODE_MASK              ((1 << OPER_CODE_BIT_COUNT) - 1)
#define REG_NUM_MASK                ((1 << REG_NUM_BIT_COUNT) - 1)

#define OPER_CODE(instr)            ((instr >> OPER_CODE_MOVE_BIT) & OPER_CODE_MASK)

#define INT_AFTER_OPER(instr)       IntValue(instr, OPER_CODE_MOVE_BIT)
#define INT_AFTER_OPER_FLAG(instr)  (instr & (1 << (OPER_CODE_MOVE_BIT - 1)))
#define INT_AFTER_OPER_WITH_FLAG(instr) IntValue(instr, OPER_CODE_MOVE_BIT - 1)

#define REG_NUM1_MOVE_BIT           (OPER_CODE_MOVE_BIT - REG_NUM_BIT_COUNT)
#define REG_NUM1_MASK               REG_NUM_MASK
#define REG_NUM1(instr)             ((instr >> REG_NUM1_MOVE_BIT) & REG_NUM1_MASK)

#define INT_AFTER_NUM1(instr)       IntValue(instr, REG_NUM1_MOVE_BIT)
#define INT_AFTER_NUM1_FLAG(instr)  (instr & (1 << (REG_NUM1_MOVE_BIT - 1)))
#define INT_AFTER_NUM1_WITH_FLAG(instr) IntValue(instr, REG_NUM1_MOVE_BIT - 1)

#define REG_NUM2_MOVE_BIT           (REG_NUM1_MOVE_BIT - REG_NUM_BIT_COUNT)
#define REG_NUM2_MASK               REG_NUM_MASK
#define REG_NUM2(instr)             ((instr >> REG_NUM2_MOVE_BIT) & REG_NUM2_MASK)

#define REG_NUM3_MOVE_BIT           0
#define REG_NUM3_MASK               REG_NUM_MASK
#define REG_NUM3(instr)             ((instr >> REG_NUM3_MOVE_BIT) & REG_NUM3_MASK)

#define INT_AFTER_NUM2(instr)       IntValue(instr, REG_NUM2_MOVE_BIT)
#define INT_AFTER_NUM2_FLAG(instr)  (instr & (1 << (REG_NUM2_MOVE_BIT - 1)))
#define INT_AFTER_NUM2_WITH_FLAG(instr)  IntValue(instr, REG_NUM2_MOVE_BIT - 1)
