#pragma once

#include "lc3sim.h"

#ifdef LC3_32BIT
#define swap swap32

uint32_t swap32(uint32_t val);
#else
#define swap swap16

uint16_t swap16(uint16_t val);
#endif

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define ARRAY_SWAP(data) do { for (size_t i = 0; i < ARRAY_SIZE(data); ++i) data[i] = swap(data[i]); } while(0)

class TestIO: public LC3_Sim::IInputOutput
{
public:
    virtual LC3_Sim::Char GetChar() const override;

    virtual void PutChar(LC3_Sim::Char a_Word) override;
    
    virtual LC3_Sim::Bool CheckKeyboard() const override;
};

class TestVM: public LC3_Sim::IVirtualMemory
{
public:
    TestVM();
    
    virtual LC3_Sim::IVirtualMemory::Result Read(LC3_Sim::RegType* a_Value, LC3_Sim::AddressType a_Address) const override;

    virtual LC3_Sim::IVirtualMemory::Result Write(LC3_Sim::RegType a_Value, LC3_Sim::AddressType a_Address) override;

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


