#include "../gtest/gtest.h"

#include "lc3sim.h"

#ifdef LC3_32BIT
#define swap swap32

static uint32_t swap32(uint32_t val) {
    return (val << 8 * 3) | ((val << 8) & 0x00FF0000) | ((val >> 8) & 0x0000FF00) | (val >> 8 * 3);
}
#else
#define swap swap16

static uint16_t swap16(uint16_t val) {
    return (val << 8) | (val >> 8);
}
#endif

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define ARRAY_SWAP(data) do { for (size_t i = 0; i < ARRAY_SIZE(data); ++i) data[i] = swap(data[i]); } while(0)


class TestIO: public LC3_Sim::IInputOutput
{
public:
    virtual LC3_Sim::Char GetChar() const override
    {
        LC3_Sim::Char ret = getchar();
        DEBUG_TRACE("GetChar %c\n", ret);
        return ret;
    }

    virtual void PutChar(LC3_Sim::Char a_Word) override
    {
        DEBUG_TRACE("PutChar %c\n", a_Word);
        putchar(a_Word);
        fflush(stdout);
    }
    
    virtual LC3_Sim::Bool CheckKeyboard() const override
    {
        static fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        return select(1, &read_fds, NULL, NULL, &timeout) ? true : false;
    }
};

class TestVM: public LC3_Sim::IVirtualMemory
{
public:
    TestVM()
    {
        m_Memory.resize(LC3_MAX_MEMORY_ADDRESS);
    }
    
    virtual LC3_Sim::IVirtualMemory::Result Read(LC3_Sim::RegType* a_Value, LC3_Sim::AddressType a_Address) const override
    {
        if (a_Address > m_Memory.size())
            return rErrorAddressOutOfRange;
        
        *a_Value = m_Memory[a_Address];
        return rSuccess;
    }

    virtual LC3_Sim::IVirtualMemory::Result Write(LC3_Sim::RegType a_Value, LC3_Sim::AddressType a_Address) override
    {
        if (a_Address > m_Memory.size())
            return rErrorAddressOutOfRange;
        
        m_Memory[a_Address] = a_Value;
        return rSuccess;
    }

    std::vector<LC3_Sim::RegType> m_Memory;
};

#ifdef LC3_32BIT
extern unsigned char lc3os32_obj[];
extern unsigned int lc3os32_obj_len;
#define lc3os_bin_data lc3os32_obj
#define lc3os_bin_data_len lc3os32_obj_len
#else
extern unsigned char lc3os_obj[];
extern unsigned int lc3os_obj_len;
#define lc3os_bin_data lc3os_obj
#define lc3os_bin_data_len lc3os_obj_len
#endif

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

    EXPECT_EQ(instr, 1); // Stop on NOP=0u
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

    EXPECT_EQ(instr, 1); // Stop on NOP=0u
    EXPECT_EQ(res, LC3_Sim::Processor::lrSuccess);
}
