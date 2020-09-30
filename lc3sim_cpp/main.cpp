// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

#include <stdio.h>
#include <vector>

#include <sys/time.h>

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "lc3sim.h"
#include "os.h"


class SimpleIO: public LC3_Sim::IInputOutput
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

class SimpleVM: public LC3_Sim::IVirtualMemory
{
public:
    SimpleVM()
    {
        m_Memory = (LC3_Sim::RegType*)malloc(LC3_MAX_MEMORY_ADDRESS * sizeof(LC3_Sim::RegType));
    }

    ~SimpleVM()
    {
        free(m_Memory);
    }
    
    virtual LC3_Sim::IVirtualMemory::Result Read(LC3_Sim::RegType* a_Value, LC3_Sim::AddressType a_Address) const override
    {
        if (a_Address >= LC3_MAX_MEMORY_ADDRESS)
            return rErrorAddressOutOfRange;
        
        *a_Value = m_Memory[a_Address];
        return rSuccess;
    }

    virtual LC3_Sim::IVirtualMemory::Result Write(LC3_Sim::RegType a_Value, LC3_Sim::AddressType a_Address) override
    {
        if (a_Address >= LC3_MAX_MEMORY_ADDRESS)
            return rErrorAddressOutOfRange;
        
        m_Memory[a_Address] = a_Value;
        return rSuccess;
    }
private:
    LC3_Sim::RegType* m_Memory;
};

class SimpleOp: public LC3_Sim::IReservedOperation
{
public:
    virtual void Operation(LC3_Sim::RegType a_RegValue, LC3_Sim::RegType a_Value) override
    {
        printf("ReservedOperation reg = %ld val = %ld\n", (long int)a_RegValue, (long int)a_Value);
    }
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
    SimpleOp simpleop;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &simpleop, &config);
    
    LC3_Sim::Processor::LoadResult res = proc.LoadData(lc3os_bin_data, lc3os_bin_data_len);
    
    if (res == LC3_Sim::Processor::lrSuccess)
        res = proc.LoadObjFile(argv[1]);

    switch (res)
    {
        case LC3_Sim::Processor::lrSuccess:
            break;

        case LC3_Sim::Processor::lrFileNotFound:
            printf("%s: Failed to load input.\n", argv[0]);
            return 1;

        case LC3_Sim::Processor::lrWriteError:
            printf("%s: Failed to load input: Write error.\n", argv[0]);
            return 1;

        case LC3_Sim::Processor::lrFileTooLarge:
            printf("%s: Failed to load input: Input exceeded memory space.\n", argv[0]);
            return 1;
    }

    LC3_Sim::InstructionIndex instr = 0;
    bool stop = false;
    int run_count = 0;
    while(!stop && (run_count < 10))
    {
        stop = proc.Run(&instr, 0x2FFFFFFF);
        ++run_count;
    }

    return 0;
}
