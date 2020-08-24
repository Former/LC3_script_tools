#include "../gtest/gtest.h"

#include "common.h"

TEST(LC3SIM_CPP, Create_Destroy)
{
    TestIO simpleio;
    TestVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config);
}

TEST(LC3SIM_CPP, LoadOS)
{
    TestIO simpleio;
    TestVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config);

    LC3_Sim::Processor::LoadResult res = proc.LoadData(lc3os_bin_data, lc3os_bin_data_len);
    
    EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
}

#ifdef LC3_32BIT
#   define BIG_DATA 0xFFFFFFu
#else
#   define BIG_DATA 0x1FFFu
#endif

TEST(LC3SIM_CPP, LoadDataNopOn0)
{
    LC3_Sim::RegType data[] = {0u, 0u, 0xFFu, BIG_DATA};
    
    ARRAY_SWAP(data);

    TestIO simpleio;
    TestVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config);

    LC3_Sim::Processor::LoadResult res = proc.LoadData((uint8_t*)data, sizeof(data));

    LC3_Sim::RegType out[3] = {1, 1, 1};

    for (int i = 0; i < 3; ++i)
        out[i] = simplevm.m_Memory[i];

    EXPECT_EQ(out[0], 0u);
    EXPECT_EQ(out[1], 0xFFu);
    EXPECT_EQ(out[2], BIG_DATA);

    EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
}

TEST(LC3SIM_CPP, LoadDataNopOn100)
{
    LC3_Sim::RegType data[] = {100u, 0u, 0xFFu, BIG_DATA};
    
    ARRAY_SWAP(data);

    TestIO simpleio;
    TestVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config);

    LC3_Sim::Processor::LoadResult res = proc.LoadData((uint8_t*)data, sizeof(data));

    LC3_Sim::RegType out[3] = {1, 1, 1};

    for (int i = 0; i < 3; ++i)
        out[i] = simplevm.m_Memory[100 + i];

    EXPECT_EQ(out[0], 0u);
    EXPECT_EQ(out[1], 0xFFu);
    EXPECT_EQ(out[2], BIG_DATA);

    EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
}

TEST(LC3SIM_CPP, RunNopOn0)
{
    LC3_Sim::RegType data[] = {0u, 0u, 0xFFu, BIG_DATA};
    
    ARRAY_SWAP(data);

    TestIO simpleio;
    TestVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config);

    LC3_Sim::Processor::LoadResult res = proc.LoadData((uint8_t*)data, sizeof(data));

    LC3_Sim::InstructionIndex instr = 0;
    proc.Run(&instr, 0xFFF);

    EXPECT_EQ(instr, 1u); // Stop on NOP=0u
    EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
}

TEST(LC3SIM_CPP, RunNopOn100)
{
    LC3_Sim::RegType data[] = {100u, 0u, 0xFFu, BIG_DATA};
    
    ARRAY_SWAP(data);

    TestIO simpleio;
    TestVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config);

    LC3_Sim::Processor::LoadResult res = proc.LoadData((uint8_t*)data, sizeof(data));

    LC3_Sim::InstructionIndex instr = 0;
    proc.Run(&instr, 0xFFF);

    EXPECT_EQ(instr, 1u); // Stop on NOP=0u
    EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
}
