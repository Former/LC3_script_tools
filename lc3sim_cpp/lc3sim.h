// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

namespace LC3_Sim
{

typedef uint16_t RegType;
typedef char Char;

class IInputOutput
{
public:
    virtual ~IInputOutput() {}
    
    virtual char GetChar() const = 0;

    virtual void PutChar() = 0;
};

struct Registers
{
    enum RegName
    {
        RN_REG_0 = 0,
        RN_REG_1,
        RN_REG_2,
        RN_REG_3,
        RN_REG_4,
        RN_REG_5,
        RN_REG_6,
        RN_REG_7,
        RN_REG_PC,
        RN_REG_PSR,
        RN_COUNT,
    };
    
    RegType m_Reg[RN_COUNT];
};

class Processor
{
public: // Types
    typedef size_t InstructionIndex;
    typedef RegType AddresType;
    
    typedef enum {
        // Success
        RC_SUCCESS,
        RC_NOP,
        // Errors
        RC_NOT_IMPLEMENTED,
        RC_ERROR_ADDRES_OUT_OF_RANGE,
    } ResultCode;

public: // Functions
    Processor(Registers* a_Registers, VirtualMemoryType* a_VirtualMemory, IInputOutput* a_InputOutput);
    
    InstructionIndex Run(InstructionIndex a_InsructCount);
    
private:
    Registers*          m_Registers;
    VirtualMemoryType*  m_VirtualMemory;
    IInputOutput*       m_InputOutput;
};


} // namespace LC3_Sim
