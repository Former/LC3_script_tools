// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

namespace LC3_Sim
{

typedef char        Char;
typedef bool        Bool;
typedef uint16_t    RegType;
typedef size_t      InstructionIndex;
typedef RegType     AddressType;

class IInputOutput
{
public:
    virtual ~IInputOutput() {}
    
    virtual Char GetChar() const = 0;

    virtual void PutChar(Char a_Word) = 0;
};

class IVirtualMemory
{
public:
    enum Result
    {
        rSuccess,
        rErrorAddressOutOfRange,
        rErrorAccess,
    };

    virtual ~IVirtualMemory() {}
    
    virtual Result Read(RegType* a_Value, AddressType a_Address) const = 0;

    virtual Result Write(RegType a_Value, AddressType a_Address) = 0;
};

// Регистры процессора.
struct Registers
{
    Registers()
    {
        m_Reg = {0};
    }
    
    enum RegName
    {
        rnReg_0 = 0,
        rnReg_1,
        rnReg_2,
        rnReg_3,
        rnReg_4,
        rnReg_5,
        rnReg_6,
        rnReg_7,
        rnReg_PC,  // Командный регистр
        rnReg_PSR, // Регистр флагов
        rnCount,
    };
    
    RegType m_Reg[rnCount];
};

// Параметры конфигурации процессора.
struct ProcessorConfig
{
    ProcessorConfig(AddressType a_ExceptionHandlerAddress, AddressType a_ExceptionMask)
        :m_ExceptionHandlerAddress(a_ExceptionHandlerAddress),m_ExceptionMask(a_ExceptionMask)
    {
        m_ExceptionCount = 0;
    }
    
    AddressType m_ExceptionHandlerAddress;
    RegType     m_ExceptionMask;
    RegType     m_ExceptionCount;
}

// InstructionExecuter выполняет одну инструкцию
class InstructionExecuter
{
private:
    struct Exception
    {
        enum Type
        {
            // Программа завершилась успешно
            etSuccess          = 0x00,
            etNop              = 0x01,
            // Ошибки - необходимо запустить exception handler
            etNotImplemented   = 0x02,
            etErrorRead        = 0x04,
            etErrorWrite       = 0x08,
        };
        Type            m_Type;
        AddressType     m_AccessAddress;
        AddressType     m_ExecuteAddress;

        Exception()
        {
            m_Type = etSuccess;
            m_AccessAddress = 0;
            m_ExecuteAddress = 0;
        }
        Exception(ExceptionType a_Type, AddressType a_ExecuteAddress, AddressType a_AccessAddress)
            :m_Type(a_Type), m_AccessAddress(a_ExecuteAddress), m_ExecuteAddress(a_AccessAddress)
        {
        }
    };
public:
    InstructionExecuter(Registers* a_Registers, IVirtualMemory* a_VirtualMemory, IInputOutput* a_InputOutput);

    Exception ExecuteOneInstruction();

private:
    Registers*      m_Registers;
    IVirtualMemory* m_VirtualMemory;
    IInputOutput*   m_InputOutput;
};

// Процессор исполняет серию инструкций, обрабатывает исключения
class Processor
{
public:
    Processor(Registers* a_Registers, IVirtualMemory* a_VirtualMemory, IInputOutput* a_InputOutput, ProcessorConfig* a_ProcessorConfig);
    
    void Run(InstructionIndex* a_ExecutedInsructionsCount, InstructionIndex a_MaxExecuteInsructCount);

    LoadResult LoadObjFile(const char* a_FileName);

    LoadResult LoadData(const unsigned uint8_t* a_Data, size_t a_DataLen);

    enum LoadResult
    {
        lrSuccess,
        lrFileNotFound,
        lrFileTooLarge,
        lrWriteError,
    };
    
private:
    Registers*       m_Registers;
    IVirtualMemory*  m_VirtualMemory;
    IInputOutput*    m_InputOutput;
    ProcessorConfig* m_ProcessorConfig;
};

} // namespace LC3_Sim
