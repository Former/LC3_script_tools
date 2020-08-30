#include "../gtest/gtest.h"

#include "common.h"
#include "instr_converter.h"

#define REG_TYPE_FROM LC3_Sim::LC3_RegisterType_16
#define INSTR_BIT_COUNT_FROM BIT_COUNT(REG_TYPE_FROM)
#define OPER_BIT_COUNT_FROM 4 
#define REG_NUM_BIT_COUNT_FROM 3

#define REG_TYPE_TO LC3_Sim::LC3_RegisterType_64
#define INSTR_BIT_COUNT_TO BIT_COUNT(REG_TYPE_TO)
#define OPER_BIT_COUNT_TO 4
#define REG_NUM_BIT_COUNT_TO 3

#define TEST_INSTR_CONVERT(i_from) LC3_INSTR_CONVERT(i_from, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO)

TEST(LC3SIM_CPP_Instr_Converter16_to_64, BR1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_BR(1, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_BR(1, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, BR2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_BR(2, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_BR(2, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, BR3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_BR(0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_BR(0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LD1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LD(3, 11, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LD(3, 11, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LD2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LD(4, -6, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LD(4, -6, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, ST1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ST(6, 12, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ST(6, 12, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, ST2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ST(7, -7, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ST(7, -7, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LDI1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDI(3, 11, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDI(3, 11, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LDI2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDI(4, -6, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDI(4, -6, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, STI1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STI(6, 12, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STI(6, 12, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, STI2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STI(7, -7, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STI(7, -7, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LEA1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LEA(6, 12, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LEA(6, 12, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LEA2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LEA(7, -7, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LEA(7, -7, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter16_to_64, ADD_I1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_I(1, 2, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_I(1, 2, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, ADD_I2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_I(2, 3, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_I(2, 3, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, ADD_I3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_I(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_I(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, ADD_R1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_R(1, 2, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_R(1, 2, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, ADD_R2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_R(2, 3, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_R(2, 3, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, AND_I1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_I(1, 2, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_I(1, 2, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, AND_I2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_I(2, 3, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_I(2, 3, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, AND_R1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_R(1, 2, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_R(1, 2, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, AND_R2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_R(2, 3, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_R(2, 3, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, AND_R3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_R(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_R(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter16_to_64, JSR_I1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_I(10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_I(10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, JSR_I2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_I(-15, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_I(-15, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, JSR_I3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_I(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_I(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, JSR_R1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_R(5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_TO);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_R(5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, JSR_R2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_R(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_TO);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_R(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter16_to_64, LDR1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDR(1, 3, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDR(1, 3, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LDR2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDR(2, 4, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDR(2, 4, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, LDR3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDR(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDR(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, STR1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STR(1, 3, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STR(1, 3, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, STR2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STR(2, 4, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STR(2, 4, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, STR3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STR(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STR(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter16_to_64, NOT1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_NOT(2, 4, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_NOT(2, 4, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, NOT2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_NOT(0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_NOT(0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, JMP1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JMP(4, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JMP(4, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, JMP2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JMP(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JMP(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter16_to_64, RTI1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_RTI(14, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_RTI(14, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, RTI2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_RTI(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_RTI(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter16_to_64, RES1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_RES(24, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_RES(24, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, RES2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_RES(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_RES(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, TRAP1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_TRAP(0x24, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_TRAP(0x24, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter16_to_64, TRAP2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_TRAP(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_TRAP(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}
