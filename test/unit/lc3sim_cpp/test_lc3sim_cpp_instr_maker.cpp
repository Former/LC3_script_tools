#include "../gtest/gtest.h"

#include "common.h"
#include "instr_config.h"

#define INFO_EXCEPTION_HANDLER 0x1u
#define START_EXCEPTION_HANDLER 20u

class TestInstrMaker : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_SimpleIO  = new TestIO;
        m_SimpleVM  = new TestVM;
        m_SimpleOP  = new TestOp;
        m_Reg       = new LC3_Sim::Registers;
        m_Config    = new LC3_Sim::ProcessorConfig(START_EXCEPTION_HANDLER, INFO_EXCEPTION_HANDLER, 0xFFF);
        m_Proc      = new LC3_Sim::Processor(m_Reg, m_SimpleVM, m_SimpleIO, m_SimpleOP, m_Config);
    }

    void TearDown()
    {
        delete m_Proc;
        delete m_SimpleIO;
        delete m_SimpleVM;
        delete m_SimpleOP;
        delete m_Reg;
        delete m_Config;
    }

    void LoadData(LC3_Sim::RegType* a_Data, size_t a_DataSize)
    {
        for (size_t i = 0; i < a_DataSize; ++i)
            a_Data[i] = LC3_SWAP(a_Data[i]);

        LC3_Sim::Processor::LoadResult res = m_Proc->LoadData((uint8_t*)a_Data, sizeof(LC3_Sim::RegType) * a_DataSize);

        EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
    }

    void Run(LC3_Sim::InstructionIndex a_InstrCount)
    {
        LC3_Sim::InstructionIndex instr = 0;
        m_Proc->Run(&instr, 0xFFF);

        EXPECT_EQ(instr, a_InstrCount);
    }

    TestIO* m_SimpleIO;
    TestVM* m_SimpleVM;
    TestOp* m_SimpleOP;
    LC3_Sim::Registers* m_Reg;

    LC3_Sim::ProcessorConfig* m_Config;
    LC3_Sim::Processor* m_Proc;
};

#define LOCAL_VAR_COPY \
    /*TestIO io = *m_SimpleIO;*/ \
    TestVM vm = *m_SimpleVM; \
    TestOp op = *m_SimpleOP; \
    LC3_Sim::Registers reg = *m_Reg; \
    LC3_Sim::ProcessorConfig config = *m_Config;

#define CHECK_LOCAL_VAR \
    /*EXPECT_EQ(io == *m_SimpleIO, true);*/ \
    EXPECT_EQ(m_SimpleOP->m_RegValue1, op.m_RegValue1); \
    EXPECT_EQ(m_SimpleOP->m_RegValue2, op.m_RegValue2); \
    EXPECT_EQ(m_SimpleOP->m_Value, op.m_Value); \
    EXPECT_EQ(m_SimpleVM->m_Memory, vm.m_Memory); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_0], reg.m_Reg[LC3_Sim::Registers::rnReg_0]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_1], reg.m_Reg[LC3_Sim::Registers::rnReg_1]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_2], reg.m_Reg[LC3_Sim::Registers::rnReg_2]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_3], reg.m_Reg[LC3_Sim::Registers::rnReg_3]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_4], reg.m_Reg[LC3_Sim::Registers::rnReg_4]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_5], reg.m_Reg[LC3_Sim::Registers::rnReg_5]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_6], reg.m_Reg[LC3_Sim::Registers::rnReg_6]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_7], reg.m_Reg[LC3_Sim::Registers::rnReg_7]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_PC], reg.m_Reg[LC3_Sim::Registers::rnReg_PC]); \
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_NumCC], reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC]); \
    EXPECT_EQ(m_Config->m_ExceptionHandlerAddress, config.m_ExceptionHandlerAddress); \
    EXPECT_EQ(m_Config->m_ExceptionInfoAddress, config.m_ExceptionInfoAddress); \
    EXPECT_EQ(m_Config->m_ExceptionMask, config.m_ExceptionMask); \
    EXPECT_EQ(m_Config->m_ExceptionCount, config.m_ExceptionCount); 

#define START_ADDRESS 10u

TEST_F(TestInstrMaker, TestNop)
{
    LC3_Sim::RegType data[] = {START_ADDRESS, MAKE_INSTR_NOP, 0xFFu, 0xFFFu, 0u};  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = 1u;
    Run(instr); // Stop on NOP=0u
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestBR_pos)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_BR(LC3_Sim::Registers::flagPositive, 1), // if (cur_pzn == LC3_Sim::Registers::flagPositive) reg_pc += 1;
        MAKE_INSTR_ADD_I(0, 0, 10), // reg[0] = reg[0] + 10; // 20
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr - 1);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestBR_neg)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, -1), // reg[0] = reg[1] - 1; // -1
        MAKE_INSTR_BR(LC3_Sim::Registers::flagNegative, 1), // if (cur_pzn == LC3_Sim::Registers::flagNegative) reg_pc += 1;
        MAKE_INSTR_ADD_I(0, 0, 10), // reg[0] = reg[0] + 10; // 9
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr - 1);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = -1;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestBR_zero)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, -1), // reg[0] = reg[1] - 1; // -1
        MAKE_INSTR_BR(LC3_Sim::Registers::flagZero, 1), // if (cur_pzn == LC3_Sim::Registers::flagZero) reg_pc += 1;
        MAKE_INSTR_ADD_I(0, 0, 10), // reg[0] = reg[0] + 10; // 9
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 9;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestBR_zero1)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 0), // reg[0] = reg[1] + 0; // 0
        MAKE_INSTR_BR(LC3_Sim::Registers::flagZero, 1), // if (cur_pzn == LC3_Sim::Registers::flagZero) reg_pc += 1;
        MAKE_INSTR_ADD_I(0, 0, 10), // reg[0] = reg[0] + 10; // 10
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr - 1);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 0;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestADDi)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_ADD_I(1, 0, 5), // reg[1] = reg[0] + 5; // 15
        MAKE_INSTR_ADD_I(5, 0, -5), // reg[5] = reg[0] - 5; // 5
        MAKE_INSTR_ADD_I(2, 3, -15), // reg[2] = reg[3] - 15; // -15
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 15;
    reg.m_Reg[LC3_Sim::Registers::rnReg_5] = 5;
    reg.m_Reg[LC3_Sim::Registers::rnReg_2] = -15 ;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 2;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestADDr)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_ADD_R(1, 0, 0), // reg[1] = reg[0] + reg[0]; // 20
        MAKE_INSTR_ADD_R(2, 0, 1), // reg[2] = reg[0] + reg[1]; // 30
        MAKE_INSTR_ADD_R(3, 1, 0), // reg[3] = reg[1] + reg[0]; // 30
        MAKE_INSTR_ADD_R(4, 2, 3), // reg[4] = reg[2] + reg[3]; // 60
        MAKE_INSTR_ADD_R(5, 4, 4), // reg[5] = reg[4] + reg[4]; // 120
        MAKE_INSTR_ADD_R(6, 4, 5), // reg[6] = reg[4] + reg[5]; // 180
        MAKE_INSTR_ADD_R(7, 0, 7), // reg[7] = reg[0] + reg[7]; // 10
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 20;
    reg.m_Reg[LC3_Sim::Registers::rnReg_2] = 30;
    reg.m_Reg[LC3_Sim::Registers::rnReg_3] = 30;
    reg.m_Reg[LC3_Sim::Registers::rnReg_4] = 60;
    reg.m_Reg[LC3_Sim::Registers::rnReg_5] = 120;
    reg.m_Reg[LC3_Sim::Registers::rnReg_6] = 180;
    reg.m_Reg[LC3_Sim::Registers::rnReg_7] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 7;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestLD)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_LD(1, 1), // reg[1] = *(reg_pc + 1);
        MAKE_INSTR_NOP,
        123u,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 123u;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestST)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_ST(0, 1), // *(reg_pc + 1) = reg[0];
        MAKE_INSTR_NOP,
        123u,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;

    vm.m_Memory[START_ADDRESS + instr] = 10u;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestJSR_I)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_JSR_I(1), // reg_pc += 1;
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_NOP,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr - 1);

    reg.m_Reg[LC3_Sim::Registers::rnReg_7] += START_ADDRESS + 1;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestJSR_Im)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_JSR_I(-3), // reg_pc += 1;
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_NOP,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    Run(2);

    reg.m_Reg[LC3_Sim::Registers::rnReg_7] += START_ADDRESS + 1;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] = START_ADDRESS - 1;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestJSR_R)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_LEA(0, 3), // reg[0] = reg_pc + 3;
        MAKE_INSTR_JSR_R(0), // swap(&reg[0], &reg_pc);
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_NOP,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr - 1);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] += START_ADDRESS + 4;
    reg.m_Reg[LC3_Sim::Registers::rnReg_7] += START_ADDRESS + 2;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr + 1;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestANDi)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_AND_I(1, 0, 6), // reg[1] = reg[0] & 6; // 10 & 6
        MAKE_INSTR_AND_I(5, 0, -5), // reg[5] = reg[0] & -5; 10 & -5
        MAKE_INSTR_AND_I(2, 3, -15), // reg[2] = reg[3] & - 15; // 10 & -15
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 10 & 6;
    reg.m_Reg[LC3_Sim::Registers::rnReg_5] = 10 & -5;
    reg.m_Reg[LC3_Sim::Registers::rnReg_2] = 10 & -15 ;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 2;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestANDr)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_ADD_I(1, 2, 6), // reg[1] = reg[2] + 6; // 6
        MAKE_INSTR_AND_R(2, 0, 1), // reg[2] = reg[0] & reg[1]; // 10 & 6
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 6;
    reg.m_Reg[LC3_Sim::Registers::rnReg_2] = 10 & 6;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 2;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestLDR)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS,
        MAKE_INSTR_LEA(4, 2), // reg[4] = reg_pc + 2;
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_LDR(1, 4, 1), // reg[1] = *(reg[4] + 1);
        MAKE_INSTR_NOP,
        123u,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 123u;
    reg.m_Reg[LC3_Sim::Registers::rnReg_4] = START_ADDRESS + 3;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestSTR)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS,
        MAKE_INSTR_LEA(4, 2), // reg[4] = reg_pc + 2;
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_STR(0, 4, 1), // *(reg[4] + 1) = reg[0];
        MAKE_INSTR_NOP,
        123u,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_4] = START_ADDRESS + 3;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;

    vm.m_Memory[START_ADDRESS + instr] = 10u;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestNOT)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 5), // reg[0] = reg[1] + 5; // 5
        MAKE_INSTR_NOT(1, 0), // reg[1] = ~reg[0];
        MAKE_INSTR_NOP
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 5;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = ~5;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestLDI)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_LDI(1, 1), // reg[1] = **(reg_pc + 1);
        MAKE_INSTR_NOP,
        START_ADDRESS + 4,
        123u,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 2;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 123u;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestSTI)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_STI(0, 1), // **(reg_pc + 1) = reg[0];
        MAKE_INSTR_NOP,
        START_ADDRESS + 4,
        123u,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 2;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;

    vm.m_Memory[START_ADDRESS + instr + 1] = 10u;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestJMP)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_LEA(0, 3), // reg[0] = reg_pc + 3;
        MAKE_INSTR_JMP(0), // reg_pc = reg[0];
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_NOP,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr - 1);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] += START_ADDRESS + 4;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr + 1;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 0;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestLEA)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_LEA(0, 3), // reg[0] = reg_pc + 3;
        MAKE_INSTR_LEA(1, -3), // reg[0] = reg_pc - 3;
        MAKE_INSTR_LEA(2, 0), // reg[0] = reg_pc;
        MAKE_INSTR_NOP,
    };  
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] += START_ADDRESS + 4;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] += START_ADDRESS - 1;
    reg.m_Reg[LC3_Sim::Registers::rnReg_2] += START_ADDRESS + 3;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 2;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, Test_EXCEPTION_HANDLER)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_LDI(1, 2), // reg[1] = **(reg_pc + 2);
        MAKE_INSTR_ADD_I(4, 0, 1), // reg[4] = reg[0] + 1; // 11
        MAKE_INSTR_NOP,
        LC3_Sim::RegType(m_SimpleVM->m_Memory.size() + 1),
    };  

    LC3_Sim::RegType ex_handler_data[] = 
    {
        START_EXCEPTION_HANDLER, 
        MAKE_INSTR_LDI(1, 2), // reg[1] = **(reg_pc + 2);
        MAKE_INSTR_ADD_I(1, 1, 1), // reg[1] += 1;
        MAKE_INSTR_JMP(1), // reg_pc = reg[1];
        INFO_EXCEPTION_HANDLER,
    };  

    LoadData(ex_handler_data, ARRAY_SIZE(ex_handler_data));
    
    LoadData(data, ARRAY_SIZE(data));
    
    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 1;
    Run(instr + ARRAY_SIZE(ex_handler_data) - 2);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = START_ADDRESS + 2;
    reg.m_Reg[LC3_Sim::Registers::rnReg_4] = 11u;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 4;
    config.m_ExceptionCount = 1;
    vm.m_Memory[INFO_EXCEPTION_HANDLER] = START_ADDRESS + 1;    
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, Test_EXCEPTION_HANDLER_mask)
{
    LC3_Sim::RegType data[] = 
    {
        START_ADDRESS, 
        MAKE_INSTR_ADD_I(0, 1, 10), // reg[0] = reg[1] + 10; // 10
        MAKE_INSTR_LDI(1, 2), // reg[1] = **(reg_pc + 2);
        MAKE_INSTR_ADD_I(4, 0, 1), // reg[4] = reg[0] + 1; // 11
        MAKE_INSTR_NOP,
        LC3_Sim::RegType(m_SimpleVM->m_Memory.size() + 1),
    };  

    LC3_Sim::RegType ex_handler_data[] = 
    {
        START_EXCEPTION_HANDLER, 
        MAKE_INSTR_LDI(1, 2), // reg[1] = **(reg_pc + 2);
        MAKE_INSTR_ADD_I(1, 1, 1), // reg[1] += 1;
        MAKE_INSTR_JMP(1), // reg_pc = reg[1];
        INFO_EXCEPTION_HANDLER,
    };  

    LoadData(ex_handler_data, ARRAY_SIZE(ex_handler_data));
    
    LoadData(data, ARRAY_SIZE(data));

    m_Config->m_ExceptionMask = 0;

    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1 - 1;
    Run(instr);
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 0;
    reg.m_Reg[LC3_Sim::Registers::rnReg_4] = 11u;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 4;
    config.m_ExceptionCount = 1;
    
    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestRTI1)
{
    LC3_Sim::RegType data[] =
    {
        START_ADDRESS,
        MAKE_INSTR_ADD_I(0, 0, 10), // reg[0] = reg[0] + 10; // 10
        MAKE_INSTR_ADD_I(1, 1, 11), // reg[0] = reg[0] + 10; // 11
        MAKE_INSTR_RTI(0, 1, 3), // RTI(reg[0] = 10, reg[1] = 11, 3);
        MAKE_INSTR_NOP,
    };

    LoadData(data, ARRAY_SIZE(data));

    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);

    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 10;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 11;
    op.m_RegValue1 = 10;
    op.m_RegValue2 = 11;
    op.m_Value = 3;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestRTI2)
{
    LC3_Sim::RegType data[] =
    {
        START_ADDRESS,
        MAKE_INSTR_ADD_I(0, 0, 0), // reg[0] = reg[0] + 0; // 0
        MAKE_INSTR_ADD_I(1, 1, 0), // reg[1] = reg[1] + 0; // 0
        MAKE_INSTR_RTI(0, 1, -15), // RTI(reg[0] = 0, reg[1] = 0, -15);
        MAKE_INSTR_NOP,
    };

    LoadData(data, ARRAY_SIZE(data));

    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);

    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = 0;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = 0;
    op.m_RegValue1 = 0;
    op.m_RegValue2 = 0;
    op.m_Value = -15;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;

    CHECK_LOCAL_VAR
}

TEST_F(TestInstrMaker, TestRTI3)
{
    LC3_Sim::RegType data[] =
    {
        START_ADDRESS,
        MAKE_INSTR_ADD_I(0, 0, -15), // reg[0] = reg[0] - 15; // -15
        MAKE_INSTR_ADD_I(1, 1, -7), // reg[1] = reg[1] - 7; // -7
        MAKE_INSTR_RTI(0, 1, 0), // RTI(reg[0] = -15, reg[1] = -7, 0);
        MAKE_INSTR_NOP,
    };

    LoadData(data, ARRAY_SIZE(data));

    LOCAL_VAR_COPY

    LC3_Sim::InstructionIndex instr = ARRAY_SIZE(data) - 1;
    Run(instr);

    reg.m_Reg[LC3_Sim::Registers::rnReg_0] = -15;
    reg.m_Reg[LC3_Sim::Registers::rnReg_1] = -7;
    op.m_RegValue1 = -15;
    op.m_RegValue2 = -7;
    op.m_Value = 0;
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] += instr;
    reg.m_Reg[LC3_Sim::Registers::rnReg_NumCC] = 1;

    CHECK_LOCAL_VAR
}

