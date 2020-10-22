#include "../gtest/gtest.h"

#include "common.h"
#include "instr_converter.h"

#define REG_TYPE_FROM LC3_Sim::LC3_RegisterType_32
#define INSTR_BIT_COUNT_FROM BIT_COUNT(REG_TYPE_FROM)
#define OPER_BIT_COUNT_FROM 4 
#define REG_NUM_BIT_COUNT_FROM 3
#define PAR_BIT_COUNT_FROM 3

#define REG_TYPE_TO LC3_Sim::LC3_RegisterType_16
#define INSTR_BIT_COUNT_TO BIT_COUNT(REG_TYPE_TO)
#define OPER_BIT_COUNT_TO 4
#define REG_NUM_BIT_COUNT_TO 3
#define PAR_BIT_COUNT_TO 3

#define TEST_INSTR_CONVERT(i_from) LC3_INSTR_CONVERT(i_from, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM, PAR_BIT_COUNT_FROM, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO, PAR_BIT_COUNT_TO)

#define BASE_NAME LC3SIM_CPP_Instr_Converter32_to_16

#include "test_lc3sim_cpp_instr_converter.h"
