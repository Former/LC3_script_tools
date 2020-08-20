// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#include "lc3sim_cpp/lc3sim.h"

#ifdef LC3_32BIT
#define Swap Swap32

static uint32_t Swap32(uint32_t val) {
    return (val << 8 * 3) | ((val << 8) & 0x00FF0000) | ((val >> 8) & 0x0000FF00) | (val >> 8 * 3);
}
#else
#define Swap Swap16

static uint16_t Swap16(uint16_t val) {
    return (val << 8) | (val >> 8);
}
#endif


virtual LC3_Sim::IInputOutput::~IInputOutput()
{
}

virtual LC3_Sim::IVirtualMemory::~IVirtualMemory()
{
}


LC3_Sim::ProcessorConfig::ProcessorConfig(AddressType a_ExceptionHandlerAddress, AddressType a_ExceptionMask)
    :m_ExceptionHandlerAddress(a_ExceptionHandlerAddress),m_ExceptionMask(a_ExceptionMask)
{
    m_ExceptionCount = 0;
}

LC3_Sim::InstructionExecuter::Exception::Exception()
{
    m_Type = etSuccess;
    m_AccessAddress = 0;
    m_ExecuteAddress = 0;
}

LC3_Sim::InstructionExecuter::Exception::Exception(ExceptionType a_Type, AddressType a_ExecuteAddress, AddressType a_AccessAddress)
    :m_Type(a_Type), m_AccessAddress(a_ExecuteAddress), m_ExecuteAddress(a_AccessAddress)
{
}

LC3_Sim::Registers::Registers()
{
    m_Reg = {0};
}
LC3_Sim::InstructionExecuter::InstructionExecuter(Registers* a_Registers, IVirtualMemory* a_VirtualMemory, IInputOutput* a_InputOutput)
    :m_Registers(a_Registers),m_VirtualMemory(a_VirtualMemory),m_InputOutput(a_InputOutput)
{
}
Exception LC3_Sim::InstructionExecuter::ExecuteOneInstruction()
{
}

LC3_Sim::Processor::Processor(Registers* a_Registers, IVirtualMemory* a_VirtualMemory, IInputOutput* a_InputOutput, ProcessorConfig* a_ProcessorConfig)
    :m_Registers(a_Registers), m_VirtualMemory(a_VirtualMemory), m_InputOutput(a_InputOutput), m_ProcessorConfig(a_ProcessorConfig)
{
}
void LC3_Sim::Processor::Run(InstructionIndex* a_ExecutedInsructionsCount, InstructionIndex a_MaxExecuteInsructCount)
{
}

LC3_Sim::Processor::LoadResult LC3_Sim::Processor::LoadObjFile(const char* a_FileName)
{
    int file_id;
    struct stat stat_buf;
    unsigned char* data;

    if ((file_id = open(a_FileName, O_RDONLY)) < 0)
        return lrFileNotFound;

    if (fstat(fd, &statbuf) < 0)
        return lrFileNotFound;

    if ((data = mmap(0, stat_buf.st_size, PROT_READ, MAP_SHARED, file_id, 0)) == MAP_FAILED)
        return lrFileNotFound;

    LoadResult res = vm_load_data(vm, data, statbuf.st_size);

    munmap(data, stat_buf.st_size);
    close(file_id);
    
    return res;
}

LC3_Sim::Processor::LoadResult LC3_Sim::Processor::LoadData(const unsigned uint8_t* a_Data, size_t a_DataLen)
{
    typedef LC3_Sim::RegType RegLoadType;
    size_t load_reg_size = sizeof(RegLoadType);

    RegLoadType* load_data = (RegLoadType*)a_Data;
    LC3_Sim::AddressType load_addr = Swap(*(load_data++));
    LC3_Sim::AddressType load_length = (a_DataLen - load_reg_size) / load_reg_size;

    for (LC3_Sim::AddressType i = 0; i < load_length; i)
    {
        IVirtualMemory::Result res = m_VirtualMemory->Write(Swap(load_data[i]), load_addr + i);
        if (res != IVirtualMemory::rSuccess)
            return lrFileTooLarge;
    }

    m_Registers->m_Reg[Registers::rnReg_PC] = load_addr;

    return lrSuccess;

}
