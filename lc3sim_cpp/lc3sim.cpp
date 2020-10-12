// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>
#include "lc3sim.h"
#include "instr_config.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>


#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define SING_BIT (1UL << LC3_SIGN_BIT_INDEX)
#define STATUS_BIT (1UL << LC3_STATUS_BIT_INDEX)

LC3_Sim::IInputOutput::~IInputOutput()
{
}

LC3_Sim::IVirtualMemory::~IVirtualMemory()
{
}

LC3_Sim::I_RTI_Operation::~I_RTI_Operation()
{
}

LC3_Sim::ProcessorConfig::ProcessorConfig(AddressType a_ExceptionHandlerAddress, AddressType a_ExceptionInfoAddress, AddressType a_ExceptionMask)
    :m_ExceptionHandlerAddress(a_ExceptionHandlerAddress),
    m_ExceptionInfoAddress(a_ExceptionInfoAddress),
    m_ExceptionMask(a_ExceptionMask)
{
    m_ExceptionCount = 0;
}

LC3_Sim::InstructionExecuter::Exception::Exception()
{
    m_Type = etSuccess;
    m_AccessAddress = 0;
    m_ExecuteAddress = 0;
}

LC3_Sim::InstructionExecuter::Exception::Exception(Type a_Type, AddressType a_ExecuteAddress, AddressType a_AccessAddress)
    :m_Type(a_Type), m_AccessAddress(a_ExecuteAddress), m_ExecuteAddress(a_AccessAddress)
{
}

LC3_Sim::Registers::Registers()
{
    m_Reg[rnReg_0] = 0UL;
    m_Reg[rnReg_1] = 0UL;
    m_Reg[rnReg_2] = 0UL;
    m_Reg[rnReg_3] = 0UL;
    m_Reg[rnReg_4] = 0UL;
    m_Reg[rnReg_5] = 0UL;
    m_Reg[rnReg_6] = 0UL;
    m_Reg[rnReg_7] = 0UL;
    m_Reg[rnReg_PC] = 0UL;
    m_Reg[rnReg_NumCC] = 0UL;
}
LC3_Sim::InstructionExecuter::InstructionExecuter(Registers* a_Registers, IVirtualMemory* a_VirtualMemory, IInputOutput* a_InputOutput, I_RTI_Operation* a_RTI_Operation)
    :m_Registers(a_Registers),m_VirtualMemory(a_VirtualMemory),m_InputOutput(a_InputOutput), m_RTI_Operation(a_RTI_Operation)
{
}

enum ESpecAddr
{
    sAddressKBSR = 0xfe00,
    sAddressKBDR = 0xfe02,
    sAddressDSR  = 0xfe04,
    sAddressDDR  = 0xfe06,
    sAddressMCR  = 0xfffe,
};

static LC3_Sim::IVirtualMemory::Result MemoryRead(LC3_Sim::RegType* a_Out, LC3_Sim::AddressType a_Address, LC3_Sim::IVirtualMemory* a_VirtualMemory, LC3_Sim::IInputOutput* a_InputOutrut)
{
    DEBUG_TRACE("MemoryRead " PRINT_REG_TYPE "\n", a_Address);
    switch (a_Address)
    {
        case sAddressKBSR:
            *a_Out = a_InputOutrut->CheckKeyboard() ? STATUS_BIT : 0;
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressKBDR:
            *a_Out = a_InputOutrut->CheckKeyboard() ? a_InputOutrut->GetChar() : 0;
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressDSR:
            *a_Out = STATUS_BIT;
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressDDR:
            *a_Out = 0;
            return LC3_Sim::IVirtualMemory::rSuccess;
    }
    
    return a_VirtualMemory->Read(a_Out, a_Address);
}

static LC3_Sim::IVirtualMemory::Result MemoryWrite(LC3_Sim::RegType a_Value, LC3_Sim::AddressType a_Address, LC3_Sim::IVirtualMemory* a_VirtualMemory, LC3_Sim::IInputOutput* a_InputOutrut)
{
    DEBUG_TRACE("MemoryWrite " PRINT_REG_TYPE ", val = " PRINT_REG_TYPE "\n", a_Address, a_Value);
    switch (a_Address)
    {
        case sAddressKBSR:
        case sAddressKBDR:
        case sAddressDSR:
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressDDR:
            a_InputOutrut->PutChar(a_Value);
            return LC3_Sim::IVirtualMemory::rSuccess;
    }

    return a_VirtualMemory->Write(a_Value, a_Address);
}

static LC3_Sim::Registers::EFlags SignFlag(LC3_Sim::RegType a_Value)
{
    if (a_Value == 0)
        return LC3_Sim::Registers::flagZero;
    else if (a_Value & SING_BIT)
        return LC3_Sim::Registers::flagNegative;
    else
        return LC3_Sim::Registers::flagPositive;
}

#define PZN_BIT_COUNT               3
#define PZN_MASK                    ((1 << PZN_BIT_COUNT) - 1)

#define REG(reg_num)                m_Registers->m_Reg[reg_num]
#define EXCEPTION(type)             LC3_Sim::InstructionExecuter::Exception(LC3_Sim::InstructionExecuter::Exception::type, REG(LC3_Sim::Registers::rnReg_PC), 0)
#define EXCEPTION_A(type, addr)     LC3_Sim::InstructionExecuter::Exception(LC3_Sim::InstructionExecuter::Exception::type, REG(LC3_Sim::Registers::rnReg_PC), addr)

#define REG_WITH_NUM1(instr)        REG(REG_NUM1(instr))
#define REG_WITH_NUM2(instr)        REG(REG_NUM2(instr))
#define REG_WITH_NUM3(instr)        REG(REG_NUM3(instr))

#define MEMORY_READ(out, addr)      MemoryRead(out, addr, m_VirtualMemory, m_InputOutput)
#define MEMORY_WRITE(value, addr)   MemoryWrite(value, addr, m_VirtualMemory, m_InputOutput)

#define SET_CC_REG_NUM1(instr)      REG(LC3_Sim::Registers::rnReg_NumCC) = REG_NUM1(instr);\
                                        DEBUG_TRACE("Reg[" PRINT_REG_TYPE "] = " PRINT_REG_TYPE "\n", REG_NUM1(instr), REG(REG_NUM1(instr)))

#define CASE(instr_name)            case OPCODE_##instr_name: DEBUG_TRACE("Operation %s\n", #instr_name);

LC3_Sim::InstructionExecuter::Exception LC3_Sim::InstructionExecuter::ExecuteOneInstruction(LC3_Sim::RegType a_Instruction)
{
    DEBUG_TRACE("Instruction " PRINT_REG_TYPE " addr " PRINT_REG_TYPE "\n", a_Instruction, REG(LC3_Sim::Registers::rnReg_PC));
    
    switch (OPER_CODE(a_Instruction))
    {
        CASE(BR)
        {
            if (a_Instruction == 0)
                return EXCEPTION(etStop); // Прерывание выполнения процессора

            LC3_Sim::RegType cur_pzn = SignFlag(REG(REG(LC3_Sim::Registers::rnReg_NumCC))) & PZN_MASK;
            LC3_Sim::RegType instr_pzn = REG_NUM1(a_Instruction) & PZN_MASK;

            if (cur_pzn & instr_pzn)
                REG(LC3_Sim::Registers::rnReg_PC) += INT_AFTER_NUM1(a_Instruction);

            break;
        }
        CASE(ADD)
        {
            if (INT_AFTER_NUM2_FLAG(a_Instruction))
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) + INT_AFTER_NUM2_WITH_FLAG(a_Instruction);
            else
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) + REG_WITH_NUM3(a_Instruction);
    
            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(LD)
        {
            LC3_Sim::AddressType addr = REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction);
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_READ(&(REG_WITH_NUM1(a_Instruction)), addr);
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorRead, addr);

            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(ST)
        {
            LC3_Sim::AddressType addr = REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction);
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_WRITE(REG_WITH_NUM1(a_Instruction), addr);

            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorWrite, addr);
                
            break;
        }
        CASE(JSR)
        {
            if (INT_AFTER_OPER_FLAG(a_Instruction))
            {
                REG(LC3_Sim::Registers::rnReg_7) = REG(LC3_Sim::Registers::rnReg_PC);
                REG(LC3_Sim::Registers::rnReg_PC) += INT_AFTER_OPER_WITH_FLAG(a_Instruction);
            }
            else
            {
                LC3_Sim::RegType tmp = REG_WITH_NUM2(a_Instruction);
                REG(LC3_Sim::Registers::rnReg_7) = REG(LC3_Sim::Registers::rnReg_PC);
                REG(LC3_Sim::Registers::rnReg_PC) = tmp;
            }

            break;
        }
        CASE(AND)
        {
            if (INT_AFTER_NUM2_FLAG(a_Instruction))
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) & INT_AFTER_NUM2_WITH_FLAG(a_Instruction);
            else
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) & REG_WITH_NUM3(a_Instruction);
    
            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(LDR)
        {
            LC3_Sim::AddressType addr = REG_WITH_NUM2(a_Instruction) + INT_AFTER_NUM2(a_Instruction);
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_READ(&(REG_WITH_NUM1(a_Instruction)), addr);
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorRead, addr);

            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(STR)
        {
            LC3_Sim::AddressType addr = REG_WITH_NUM2(a_Instruction) + INT_AFTER_NUM2(a_Instruction);
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_WRITE(REG_WITH_NUM1(a_Instruction), addr);

            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorWrite, addr);
                
            break;
        }
        CASE(RTI)
            m_RTI_Operation->Operation(REG_WITH_NUM1(a_Instruction), REG_WITH_NUM2(a_Instruction), INT_AFTER_NUM2(a_Instruction));
            break;
        CASE(NOT)
        {
            REG_WITH_NUM1(a_Instruction) = ~REG_WITH_NUM2(a_Instruction);

            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(LDI)
        {
            LC3_Sim::AddressType addr1 = REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction);
            LC3_Sim::AddressType addr2 = 0;
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_READ(&addr2, addr1);
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorRead, addr1);

            res = MEMORY_READ(&REG_WITH_NUM1(a_Instruction), addr2);
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorRead, addr2);

            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(STI)
        {
            LC3_Sim::AddressType addr1 = REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction);
            LC3_Sim::AddressType addr2 = 0;
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_READ(&addr2, addr1);
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorRead, addr1);

            res = MEMORY_WRITE(REG_WITH_NUM1(a_Instruction), addr2);
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION_A(etErrorWrite, addr2);

            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(JMP)
        {
            REG(LC3_Sim::Registers::rnReg_PC) = REG_WITH_NUM2(a_Instruction);
            break;
        }
        CASE(RES)
            return EXCEPTION(etNotImplemented);
        CASE(LEA)
        {
            REG_WITH_NUM1(a_Instruction) = REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction);

            SET_CC_REG_NUM1(a_Instruction);
            break;
        }
        CASE(TRAP)
        {
            LC3_Sim::AddressType addr = TRAP(a_Instruction);

            if (addr == 0x20)
            {
                // Для меньшей загрузки процессора в idle
                REG(LC3_Sim::Registers::rnReg_0) = m_InputOutput->GetChar();
            }
            else
            {
                // Возвращаемся в ОС после обработки исключений
                REG(LC3_Sim::Registers::rnReg_7) = REG(LC3_Sim::Registers::rnReg_PC);
                
                LC3_Sim::IVirtualMemory::Result res =
                    MEMORY_READ(&REG(LC3_Sim::Registers::rnReg_PC), addr);
            
                if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                    return EXCEPTION_A(etErrorRead, addr);
            }

            break;
        }
    }
    
    return EXCEPTION(etSuccess);
}

LC3_Sim::Processor::Processor(Registers* a_Registers, IVirtualMemory* a_VirtualMemory, IInputOutput* a_InputOutput, I_RTI_Operation* a_RTI_Operation, ProcessorConfig* a_ProcessorConfig)
    :m_Registers(a_Registers), 
    m_VirtualMemory(a_VirtualMemory), 
    m_InputOutput(a_InputOutput), 
    m_RTI_Operation(a_RTI_Operation),
    m_ProcessorConfig(a_ProcessorConfig),
    m_Executer(m_Registers, m_VirtualMemory, m_InputOutput, m_RTI_Operation)
{
}

LC3_Sim::Bool LC3_Sim::Processor::Run(InstructionIndex* a_ExecutedInsructionsCount, InstructionIndex a_MaxExecuteInsructCount)
{
    LC3_Sim::InstructionExecuter::Exception exception;
    InstructionIndex* exec_instruct = a_ExecutedInsructionsCount;
    for (*exec_instruct = 1; *exec_instruct <= a_MaxExecuteInsructCount; ++*exec_instruct)
    {
        LC3_Sim::AddressType addr = REG(LC3_Sim::Registers::rnReg_PC);
        LC3_Sim::RegType instruction = 0;
        LC3_Sim::IVirtualMemory::Result res =
            MEMORY_READ(&instruction, addr);
            
        if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
        {
            exception = EXCEPTION_A(etErrorRead, addr);
            break;
        }

        ++REG(LC3_Sim::Registers::rnReg_PC);
        
        exception = m_Executer.ExecuteOneInstruction(instruction);
        
        if (exception.m_Type == LC3_Sim::InstructionExecuter::Exception::etSuccess)
            continue;
        
        if (exception.m_Type == LC3_Sim::InstructionExecuter::Exception::etStop)
            break;
        
        // Exception handler
        ++m_ProcessorConfig->m_ExceptionCount;
        LC3_Sim::AddressType addr_of_exception = addr;
        if (!(m_ProcessorConfig->m_ExceptionMask & exception.m_Type))
            continue;

        MEMORY_WRITE(addr_of_exception, m_ProcessorConfig->m_ExceptionInfoAddress);
        REG(LC3_Sim::Registers::rnReg_PC) = m_ProcessorConfig->m_ExceptionHandlerAddress;        
    }
    
    return (exception.m_Type == LC3_Sim::InstructionExecuter::Exception::etStop) ? true : false;
}

LC3_Sim::Processor::LoadResult LC3_Sim::Processor::LoadObjFile(const char* a_FileName)
{
    int file_id;
    struct stat stat_buf;
    uint8_t* data;

    if ((file_id = open(a_FileName, O_RDONLY)) < 0)
        return lrFileNotFound;

    if (fstat(file_id, &stat_buf) < 0)
        return lrFileNotFound;

    if ((data = (uint8_t*)mmap(0, stat_buf.st_size, PROT_READ, MAP_SHARED, file_id, 0)) == MAP_FAILED)
        return lrFileNotFound;

    LoadResult res = LoadData(data, stat_buf.st_size);

    munmap(data, stat_buf.st_size);
    close(file_id);
    
    return res;
}

LC3_Sim::Processor::LoadResult LC3_Sim::Processor::LoadData(const uint8_t* a_Data, uint32_t a_DataLen)
{
    typedef LC3_Sim::RegType RegLoadType;
    size_t load_reg_size = sizeof(RegLoadType);

    RegLoadType* load_data = (RegLoadType*)a_Data;
    LC3_Sim::AddressType load_addr = LC3_SWAP(*(load_data));
    ++load_data;
    LC3_Sim::AddressType load_length = (a_DataLen - load_reg_size) / load_reg_size;

    for (LC3_Sim::AddressType i = 0; i < load_length; ++i)
    {
        IVirtualMemory::Result res = m_VirtualMemory->Write(LC3_SWAP(load_data[i]), load_addr + i);
        if (res != IVirtualMemory::rSuccess)
            return lrFileTooLarge;
    }

    m_Registers->m_Reg[Registers::rnReg_PC] = load_addr;

    return lrSuccess;
}
