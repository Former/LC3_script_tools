# LC3 script tools

LC3 script toolchain based on sources - https://github.com/edga/lc3 commit c7e8222bd74923f02a80986c83197796a725136c

## Dirs

* `/tests`: Regress, unit and speed tests.
* `/lc3tools`: Unix LC3 assembler and simulator from the book accompanying web-site.
* `/lcc-1.3`: LCC based C compiler for LC3.
* `/lc3sim-c`: A C implementation of the LC-3 virtual machine, an educational computer architecture.
* `/lc3sim_cpp`: C++ virtual machine with virtual interfaces

## Before compile

Install cmake, compiler and libs:

`sudo aptitude install cmake gcc g++ libncurses5-dev`

## Chages

* Migrate to cmake
* Regress test
* Unit test
* Speed test
* Small bash script for simple use cmake `clean_build.bash` and `rebuild_and_test.bash`
* `lc3sim_cpp` virtual machine
* 32 and 64 bit version
* `__asm` insertion in C compiler `lcc`

## Usage

### Script file

`script.c`
```c++
void some_func(void)
{
    // This code run user operation SimpleOp::Operation with value a_RegValue = 10, a_Value = 20
    __asm {
        AND R0, R0, #0 
        ADD R0, R0, #10 
        RES R0, #20
    }
}

int main()
{
    some_func();
    return 0;
}
```

### Compile script

Run `lcc` compile:

`./build/bin/lcc -target=lc3 script.c -o script`

`lcc` generate `script.asm` and `script.obj` files

;

### Run script file

Script file `script.obj` file can load with function ```LC3_Sim::Processor::LoadObjFile```, see example:

```c++
#include "lc3sim.h"
#include "os.h"

class SimpleIO: public LC3_Sim::IInputOutput
{
public:
    virtual LC3_Sim::Char GetChar() const override
    {
        return getchar();
    }

    virtual void PutChar(LC3_Sim::Char a_Word) override
    {
        putchar(a_Word);
    }
    
    virtual LC3_Sim::Bool CheckKeyboard() const override
    {
        return false;
    }
};

class SimpleVM: public LC3_Sim::IVirtualMemory
{
public:
    SimpleVM()
    {
        m_Memory.resize(LC3_MAX_MEMORY_ADDRESS);
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
    std::vector<LC3_Sim::RegType> m_Memory;
};

class SimpleOp: public LC3_Sim::IReservedOperation
{
public:
    virtual void Operation(LC3_Sim::RegType a_RegValue, LC3_Sim::RegType a_Value) override
    {
        printf("User operation reg = %ld val = %ld\n", (long int)a_RegValue, (long int)a_Value);
    }
};

int main(int argc, const char* argv[])
{
    SimpleIO simpleio;
    SimpleVM simplevm;
    SimpleOp simpleop;
    LC3_Sim::Registers reg;

    LC3_Sim::ProcessorConfig config(0, 0xfffe, 0);
    LC3_Sim::Processor proc(&reg, &simplevm, &simpleio, &simpleop, &config);
    
    LC3_Sim::Processor::LoadResult res = proc.LoadData(lc3os_bin_data, lc3os_bin_data_len);
    
    if (res == LC3_Sim::Processor::lrSuccess)
        res = proc.LoadObjFile("script.obj");

    LC3_Sim::InstructionIndex instr = 0;
    proc.Run(&instr, 0xFFFF);

    return 0;
}

```

Use one define in `LC3_16BIT`, `LC3_32BIT`, `LC3_32BIT_WIDE`, `LC3_64BIT_WIDE` to compile for some architecture.

For more info see:

* unit test `/test/unit/lc3sim_cpp/test_lc3sim_cpp_instr_maker.cpp`
* lc3sim_cpp `/lc3sim_cpp/main.cpp`
* regress test `/test/regress/__asm_test/test_res.c`
