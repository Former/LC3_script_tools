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

enum eConfig {
    cAddressMAX     = LC3_MAX_MEMORY_ADDRES,
    cAddressInitial = 0x3000,
    cSignBit        = 1 << LC3_SIGN_BIT_INDEX,
    cStatusBit      = 1 << LC3_STATUS_BIT_INDEX,
};

enum EOperCode
{
    eOperCode_BR   = 0b0000,
    eOperCode_ADD  = 0b0001,
    eOperCode_LD   = 0b0010,
    eOperCode_ST   = 0b0011,
    eOperCode_JSR  = 0b0100,
    eOperCode_AND  = 0b0101,
    eOperCode_LDR  = 0b0110,
    eOperCode_STR  = 0b0111,
    eOperCode_RTI  = 0b1000,
    eOperCode_NOT  = 0b1001,
    eOperCode_LDI  = 0b1010,
    eOperCode_STI  = 0b1011,
    eOperCode_JMP  = 0b1100,
    eOperCode_RESERVED = 0b1101,
    eOperCode_LEA  = 0b1110,
    eOperCode_TRAP = 0b1111,
};

enum ESpecAddr
{
    sAddressKBSR = 0xfe00,
    sAddressKBDR = 0xfe02,
    sAddressDSR  = 0xfe04,
    sAddressDDR  = 0xfe06,
    sAddressMCR  = 0xfffe,
};

enum EFlags {
    flagPositive = 0b001,
    flagZero     = 0b010,
    flagNegative = 0b100,
};

static LC3_Sim::RegType IntValue(LC3_Sim::RegType a_Instruct, LC3_Sim::RegType a_nBit)
{
    LC3_Sim::RegType mask = 1 << (a_nBit - 1);
    a_Instruct &= ((1 << a_nBit) - 1);
    return (a_Instruct ^ mask) - mask;
}

static LC3_Sim::IVirtualMemory::Result MemoryRead(LC3_Sim::RegType* a_Out, LC3_Sim::AddressType a_Address, LC3_Sim::IVirtualMemory* a_VirtualMemory, LC3_Sim::IInputOutput* a_InputOutrut)
{
    switch (a_Address)
    {
        case sAddressKBSR:
            *a_Out = a_InputOutrut->CheckKeyboard() ? VM_STATUS_BIT : 0;
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressKBDR:
            *a_Out = a_InputOutrut->CheckKeyboard() ? a_InputOutrut->GetChar() : 0;
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressDSR:
            *a_Out = VM_STATUS_BIT;
            return LC3_Sim::IVirtualMemory::rSuccess;
        case sAddressDDR:
            *a_Out = 0;
            return LC3_Sim::IVirtualMemory::rSuccess;
    }
    
    return a_VirtualMemory->Read(a_Out, a_Address);
}

static LC3_Sim::IVirtualMemory::Result MemoryWrite(LC3_Sim::RegType a_Value, LC3_Sim::AddressType a_Address, LC3_Sim::IVirtualMemory* a_VirtualMemory, LC3_Sim::IInputOutput* a_InputOutrut)
{
    switch (a_Address)
    {
        case sAddressKBSR:
        case sAddressKBDR:
        case sAddressDSR:
            return LC3_Sim::IVirtualMemory::rSuccess;
       case sAddressDDR:
            a_InputOutrut->PutChar(a_Value);
            return LC3_Sim::IVirtualMemory::rSuccess;

    return a_VirtualMemory->Write(a_Value, a_Address);
}

static EFlags SignFlag(LC3_Sim::RegType a_Value) {
    if (a_Value == 0)
        return flagZero;
    else if (a_Value & VM_SIGN_BIT)
        return flagNegative;
    else
        return flagPositive;
}

static void SetCC(Registers* a_Registers, LC3_Sim::RegNumType a_RegNum)
{
    a_Registers->m_Reg[LC3_Sim::Registers::rnReg_PSR] = SignFlag(a_Registers->m_Reg[a_RegNum]);
}

#define INSTRUCTION_BIT_COUNT       16
#define OPER_CODE_BIT_COUNT         4
#defien REG_NUM_BIT_COUNT           3

#define OPER_CODE_MOVE_BIT          (INSTRUCTION_BIT_COUNT - OPER_CODE_BIT_COUNT)
#define OPER_CODE_MASK              ((1 << OPER_CODE_BIT_COUNT) - 1)
#define REG_NUM_MASK                ((1 << REG_NUM_BIT_COUNT) - 1)
        
#define OPER_CODE(instr)            ((instr >> OPER_CODE_MOVE_BIT) & OPER_CODE_MASK)
        
#define REG_NUM1_MOVE_BIT           (OPER_CODE_MOVE_BIT - REG_NUM_BIT_COUNT)
#define REG_NUM1_MASK               REG_NUM_MASK
#define REG_NUM1(instr)             ((instr >> REG_NUM1_MOVE_BIT) & REG_NUM1_MASK)
        
#define REG_NUM2_MOVE_BIT           (REG_NUM1_MOVE_BIT - REG_NUM_BIT_COUNT)
#define REG_NUM2_MASK               REG_NUM_MASK
#define REG_NUM2(instr)             ((instr >> REG_NUM2_MOVE_BIT) & REG_NUM2_MASK)

#define INT_AFTER_NUM1(instr)       IntValue(instr, REG_NUM1_MOVE_BIT)
#define INT_AFTER_NUM1_FLAG(instr)  (instr & (1 << (REG_NUM1_MOVE_BIT - 1)))
#define INT_AFTER_NUM1_WITH_FLAG(instr) IntValue(instr, REG_NUM1_MOVE_BIT - 1)
        
#define REG_NUM3_MOVE_BIT           0
#define REG_NUM3_MASK               REG_NUM_MASK
#define REG_NUM3(instr)             ((instr >> REG_NUM3_MOVE_BIT) & REG_NUM3_MASK)

#define INT_AFTER_NUM2(instr)       IntValue(instr, REG_NUM2_MOVE_BIT)
#define INT_AFTER_NUM2_FLAG(instr)  (instr & (1 << (REG_NUM2_MOVE_BIT - 1)))
#define INT_AFTER_NUM2_WITH_FLAG(instr)  IntValue(instr, REG_NUM2_MOVE_BIT - 1)

#define PZN_BIT_COUNT               3
#define PZN_MASK                    ((1 << PZN_BIT_COUNT) - 1)

#define REG(reg_num)                m_Registers->m_Reg[reg_num]
#define EXCEPTION(type)             Exception(Exception::type, REG(LC3_Sim::Registers::rnReg_PC), 0)

#define REG_WITH_NUM1(instr)        REG(REG_NUM1(instr))
#define REG_WITH_NUM2(instr)        REG(REG_NUM2(instr))
#define REG_WITH_NUM3(instr)        REG(REG_NUM3(instr))

#define MEMORY_READ(out, addr)      MemoryRead(out, addr, m_VirtualMemory, m_InputOutrut);
#define MEMORY_WRITE(value, addr)   MemoryWrite(value, addr, m_VirtualMemory, m_InputOutrut);
            

LC3_Sim::InstructionExecuter::Exception LC3_Sim::InstructionExecuter::ExecuteOneInstruction(LC3_Sim::RegType a_Instruction)
{
    LC3_Sim::RegType oper_code = OPER_CODE(a_Instruction);
    
    switch (oper_code)
    {
        case eOperCode_BR:
        {
            LC3_Sim::RegType cur_pzn = REG(LC3_Sim::Registers::rnReg_PSR) & PZN_MASK;
            LC3_Sim::RegType instr_pzn = REG_NUM1(a_Instruction) & PZN_MASK;

            if (cur_pzn & instr_pzn)
                REG(LC3_Sim::Registers::rnReg_PC) += INT_AFTER_NUM1(a_Instruction);

            if (a_Instruction == 0)
                return EXCEPTION(etNop);
            
            break;
        }
        case eOperCode_ADD: 
        {
            if (INT_AFTER_NUM2_FLAG(a_Instruction))
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) + INT_AFTER_NUM2_WITH_FLAG(a_Instruction);
            else
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) + REG_WITH_NUM3(a_Instruction);
    
            SetCC(a_Registers, REG_NUM1(a_Instruction));
            break;
        }
        case eOperCode_LD:
        {
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_READ(&(REG_WITH_NUM1(a_Instruction)), REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction));
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION(etErrorRead);

            SetCC(a_Registers, REG_NUM1(a_Instruction));
            break;
        }
        case eOperCode_ST:
        {
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_WRITE(REG_WITH_NUM1(a_Instruction), REG(LC3_Sim::Registers::rnReg_PC) + INT_AFTER_NUM1(a_Instruction));

            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION(etErrorWrite);
                
            break;
        }
        case eOperCode_JSR:
        {
            if (INT_AFTER_NUM1_FLAG(a_Instruction))
            {
                REG(LC3_Sim::Registers::rnReg_7) = REG(LC3_Sim::Registers::rnReg_PC);
                REG(LC3_Sim::Registers::rnReg_PC) += INT_AFTER_NUM1_WITH_FLAG(a_Instruction);
            }
            else
            {
                LC3_Sim::RegType tmp = REG_WITH_NUM2(a_Instruction);
                REG(LC3_Sim::Registers::rnReg_7) = REG(LC3_Sim::Registers::rnReg_PC);
                REG(LC3_Sim::Registers::rnReg_PC) = tmp;
            }

            break;
        }
        case eOperCode_AND:
        {
            if (INT_AFTER_NUM2_FLAG(a_Instruction))
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) & INT_AFTER_NUM2_WITH_FLAG(a_Instruction);
            else
                REG_WITH_NUM1(a_Instruction) = REG_WITH_NUM2(a_Instruction) & REG_WITH_NUM3(a_Instruction);
    
            SetCC(a_Registers, REG_NUM1(a_Instruction));
            break;
        }
        case eOperCode_LDR:
        {
            LC3_Sim::IVirtualMemory::Result res =
                MEMORY_READ(&(REG_WITH_NUM1(a_Instruction)), REG_WITH_NUM2(a_Instruction) + INT_AFTER_NUM2(a_Instruction));
            
            if (res != LC3_Sim::IVirtualMemory::Result::rSuccess)
                return EXCEPTION(etErrorRead);

            SetCC(a_Registers, REG_NUM1(a_Instruction));
            break;
        }
    }
    
    return EXCEPTION(etSuccess);
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
