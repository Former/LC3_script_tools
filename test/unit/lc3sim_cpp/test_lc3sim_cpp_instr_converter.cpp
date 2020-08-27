#include "../gtest/gtest.h"

#include "common.h"
#include "instr_converter.h"

#define REG_TYPE_FROM LC3_Sim::LC3_RegisterType_16
#define INSTR_BIT_COUNT_FROM BIT_COUNT(REG_TYPE_FROM)
#define OPER_BIT_COUNT_FROM 4 
#define REG_NUM_BIT_COUNT_FROM 3

#define REG_TYPE_TO LC3_Sim::LC3_RegisterType_32
#define INSTR_BIT_COUNT_TO BIT_COUNT(REG_TYPE_TO)
#define OPER_BIT_COUNT_TO 4
#define REG_NUM_BIT_COUNT_TO 3

#define TEST_INSTR_CONVERT(i_from) LC3_INSTR_CONVERT(i_from, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO)

TEST(LC3SIM_CPP_Instr_Converter, BR1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_BR(1, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_BR(1, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, BR2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_BR(2, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_BR(2, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, BR3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_BR(0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_BR(0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LD1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LD(3, 11, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LD(3, 11, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LD2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LD(4, -6, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LD(4, -6, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, ST1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ST(6, 12, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ST(6, 12, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, ST2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ST(7, -7, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ST(7, -7, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LDI1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDI(3, 11, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDI(3, 11, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LDI2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDI(4, -6, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDI(4, -6, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, STI1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STI(6, 12, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STI(6, 12, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, STI2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STI(7, -7, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STI(7, -7, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LEA1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LEA(6, 12, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LEA(6, 12, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LEA2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LEA(7, -7, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LEA(7, -7, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter, ADD_I1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_I(1, 2, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_I(1, 2, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, ADD_I2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_I(2, 3, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_I(2, 3, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, ADD_I3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_I(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_I(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, ADD_R1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_R(1, 2, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_R(1, 2, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, ADD_R2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_ADD_R(2, 3, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_ADD_R(2, 3, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, AND_I1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_I(1, 2, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_I(1, 2, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, AND_I2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_I(2, 3, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_I(2, 3, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, AND_R1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_R(1, 2, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_R(1, 2, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, AND_R2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_R(2, 3, 5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_R(2, 3, 5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, AND_R3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_AND_R(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_AND_R(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter, JSR_I1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_I(10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_I(10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, JSR_I2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_I(-15, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_I(-15, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, JSR_I3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_I(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_I(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, JSR_R1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_R(5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_TO);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_R(5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, JSR_R2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_JSR_R(0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_TO);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_JSR_R(0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}


TEST(LC3SIM_CPP_Instr_Converter, LDR1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDR(1, 3, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDR(1, 3, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LDR2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDR(2, 4, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDR(2, 4, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, LDR3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_LDR(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_LDR(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, STR1)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STR(1, 3, 10, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STR(1, 3, 10, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, STR2)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STR(2, 4, -5, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STR(2, 4, -5, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}

TEST(LC3SIM_CPP_Instr_Converter, STR3)
{
    REG_TYPE_FROM i_from = LC3_MAKE_INSTR_STR(0, 0, 0, INSTR_BIT_COUNT_FROM, OPER_BIT_COUNT_FROM, REG_NUM_BIT_COUNT_FROM);
    REG_TYPE_TO i_to = LC3_MAKE_INSTR_STR(0, 0, 0, INSTR_BIT_COUNT_TO, OPER_BIT_COUNT_TO, REG_NUM_BIT_COUNT_TO);

    REG_TYPE_TO i_convert = TEST_INSTR_CONVERT(i_from);
    EXPECT_EQ(i_convert, i_to);
}