// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

#pragma once

#include <stdint.h>

namespace LC3_Sim
{

typedef uint32_t LC3_DefaultOperationType;

typedef uint32_t LC3_RegisterType_32;
typedef uint32_t LC3MemAddressType_32;

typedef uint16_t LC3_RegisterType_16;
typedef uint16_t LC3MemAddressType_16;

#define BIT_IN_ONE_BYTE_COUNT               8
#define BIT_COUNT(type)                     (sizeof(type) * BIT_IN_ONE_BYTE_COUNT)


#if defined(LC3_32BIT)

    typedef LC3_RegisterType_32 LC3_RegisterType;
    typedef LC3MemAddressType_32 LC3MemAddressType;

    #define LC3_SWAP SWAP_32
    #define LC3_MAX_MEMORY_ADDRESS (2*UINT16_MAX) // may be up to UINT32_MAX
    #define LC3_INSTRUCTION_BIT_COUNT       BIT_COUNT(LC3_Sim::LC3_RegisterType_16)

#elif defined(LC3_32BIT_WIDE)

    typedef LC3_RegisterType_32 LC3_RegisterType;
    typedef LC3MemAddressType_32 LC3MemAddressType;

    #define LC3_SWAP SWAP_32
    #define LC3_MAX_MEMORY_ADDRESS (2*UINT16_MAX) // may be up to UINT32_MAX
    #define LC3_INSTRUCTION_BIT_COUNT       BIT_COUNT(LC3_Sim::LC3_RegisterType)

#else // LC3_16BIT

    typedef LC3_RegisterType_16 LC3_RegisterType;
    typedef LC3MemAddressType_16 LC3MemAddressType;

    #define LC3_SWAP SWAP_16
    #define LC3_MAX_MEMORY_ADDRESS UINT16_MAX
    #define LC3_INSTRUCTION_BIT_COUNT       BIT_COUNT(LC3_Sim::LC3_RegisterType)

#endif

#define LC3_SIGN_BIT_INDEX (BIT_COUNT(LC3_Sim::LC3_RegisterType) - 1)
#define LC3_STATUS_BIT_INDEX (BIT_COUNT(LC3_Sim::LC3_RegisterType) - 1)

#define SWAP_32(val) ((val << (BIT_IN_ONE_BYTE_COUNT * 3)) | ((val << BIT_IN_ONE_BYTE_COUNT) & 0x00FF0000) | ((val >> BIT_IN_ONE_BYTE_COUNT) & 0x0000FF00) | (val >> (BIT_IN_ONE_BYTE_COUNT * 3)))
#define SWAP_16(val) ((val << BIT_IN_ONE_BYTE_COUNT) | (val >> BIT_IN_ONE_BYTE_COUNT))

} // namespace LC3_Sim
