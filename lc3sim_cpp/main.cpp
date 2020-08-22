// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

#include <lc3sim.h>
#include <stdio.h>
#include <vector>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>

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


class SimpleIO: public LC3_Sim::IInputOutput
{
public:
    virtual Char GetChar() const override
    {
        return getchar();
    }

    virtual void PutChar(Char a_Word) override
    {
        putchar(a_Word);
        fflush(stdout);
    }
    
    virtual Bool CheckKeyboard() const override
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

class SimpleVM: public LC3_Sim::IVirtualMemory
{
public:
    SimpleVM()
    {
        m_Memory.resize(65536);
    }
    
    virtual Result Read(RegType* a_Value, AddressType a_Address) const override
    {
        if (a_Address > m_Memory.size())
            return rErrorAddressOutOfRange;
        
        *a_Value = m_Memory[a_Address];
    }

    virtual Result Write(RegType a_Value, AddressType a_Address) override
    {
        if (a_Address > m_Memory.size())
            return rErrorAddressOutOfRange;
        
        m_Memory[a_Address] = a_Value;
    }
private:
    std::vector<LC3_Sim::RegType> m_Memory;
};

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        printf("Use: %s <lc3prog.obj>\n", argv[0]);
        return 1;
    }
    
    SimpleIO simpleio;
    SimpleVM simplevm;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &config)
    
    LC3_Sim::Processor::LoadResult res = proc.LoadData(lc3os_bin_data, lc3os_bin_data_len);
    
    if (res == LC3_Sim::Processor::lrSuccess)
        res = proc.LoadObjFile(argv[1]);

    switch (res)
    {
        case LC3_Sim::Processor::lrSuccess:
            break;

        case LC3_Sim::Processor::lrFileNotFound:
            printf("%s: Failed to load input: %s\n", argv[0], strerror(errno));
            return 1;

        case LC3_Sim::Processor::lrFileTooLarge:
            printf("%s: Failed to load input: Input exceeded memory space\n", argv[0]);
            return 1;
    }

    LC3_Sim::InstructionIndex instr = 0;
    proc.Run(&instr, 0xFFFFFF);

    return 0;
}
