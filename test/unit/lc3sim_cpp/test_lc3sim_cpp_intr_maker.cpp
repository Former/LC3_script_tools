#include "../gtest/gtest.h"

#include "common.h"
#include "instr_maker.h"

TEST(LC3SIM_CPP_INSTR_MAKER, Nop)
{
    LC3_Sim::RegType data[] = {100u, MAKE_INSTR_BR(0, 0), 0xFFu, 0xFFFu};  
    
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
