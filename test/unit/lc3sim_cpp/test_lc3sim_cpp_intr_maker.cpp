#include "../gtest/gtest.h"

#include "common.h"
#include "instr_maker.h"

class TestInstrMaker : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_SimpleIO  = new TestIO;
        m_SimpleVM  = new TestVM;
        m_Reg       = new LC3_Sim::Registers;
        m_Config    = new LC3_Sim::ProcessorConfig(0, 0xfffe, 0);
        m_Proc      = new LC3_Sim::Processor(m_Reg, m_SimpleVM, m_SimpleIO, m_Config);
    }

    void TearDown()
    {
        delete m_Proc;
        delete m_SimpleIO;
        delete m_SimpleVM;
        delete m_Reg;
        delete m_Config;
    }

    void LoadData(LC3_Sim::RegType* a_Data, size_t a_DataSize)
    {
        for (size_t i = 0; i < a_DataSize; ++i)
            a_Data[i] = swap(a_Data[i]);

        LC3_Sim::Processor::LoadResult res = m_Proc->LoadData((uint8_t*)a_Data, a_DataSize);

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
    LC3_Sim::Registers* m_Reg;

    LC3_Sim::ProcessorConfig* m_Config;
    LC3_Sim::Processor* m_Proc;
};

#define LOCAL_VAR_COPY \
    TestIO io = *m_SimpleIO; \
    TestVM vm = *m_SimpleVM; \
    LC3_Sim::Registers reg = *m_Reg; \
    LC3_Sim::ProcessorConfig config = *m_Config;

#define CHECK_LOCAL_VAR \
    /*EXPECT_EQ(io == *m_SimpleIO, true);*/ \
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
    EXPECT_EQ(m_Reg->m_Reg[LC3_Sim::Registers::rnReg_PSR], reg.m_Reg[LC3_Sim::Registers::rnReg_PSR]); \
    EXPECT_EQ(m_Config->m_ExceptionHandlerAddress, config.m_ExceptionHandlerAddress); \
    EXPECT_EQ(m_Config->m_ExceptionInfoAddress, config.m_ExceptionInfoAddress); \
    EXPECT_EQ(m_Config->m_ExceptionMask, config.m_ExceptionMask); \
    EXPECT_EQ(m_Config->m_ExceptionCount, config.m_ExceptionCount); 

TEST_F(TestInstrMaker, TestNop)
{
    LC3_Sim::RegType data[] = {100u, MAKE_INSTR_NOP, 0xFFu, 0xFFFu, 0u};  
    
    LoadData(data, sizeof(data));
    
    LOCAL_VAR_COPY    

    Run(1u); // Stop on NOP=0u
    
    reg.m_Reg[LC3_Sim::Registers::rnReg_PC] ++;
    
    CHECK_LOCAL_VAR
}



