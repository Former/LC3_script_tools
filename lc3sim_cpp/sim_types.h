// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

#pragma once

#include <stdint.h>

namespace LC3_Sim
{

#if defined(LC3_32BIT)

typedef uint32_t LC3_RegisterType;
typedef uint32_t LC3MemAddressType;

#define LC3_SWAP SWAP_32
#define LC3_MAX_MEMORY_ADDRESS (2*UINT16_MAX) // may be up to UINT32_MAX
#define LC3_INSTRUCTION_BIT_COUNT       16

#elif defined(LC3_32BIT_WIDE)

typedef uint32_t LC3_RegisterType;
typedef uint32_t LC3MemAddressType;

#define LC3_SWAP SWAP_32
#define LC3_MAX_MEMORY_ADDRESS (2*UINT16_MAX) // may be up to UINT32_MAX
#define LC3_INSTRUCTION_BIT_COUNT       (8 * sizeof(LC3_Sim::LC3_RegisterType))

#else // LC3_16BIT

typedef uint16_t LC3_RegisterType;
typedef uint16_t LC3MemAddressType;

#define LC3_SWAP SWAP_16
#define LC3_MAX_MEMORY_ADDRESS UINT16_MAX
#define LC3_INSTRUCTION_BIT_COUNT       16

#endif

#define LC3_SIGN_BIT_INDEX (sizeof(LC3_Sim::LC3_RegisterType) * 8 - 1)
#define LC3_STATUS_BIT_INDEX (sizeof(LC3_Sim::LC3_RegisterType) * 8 - 1)

#define SWAP_32(val) ((val << (8 * 3)) | ((val << 8) & 0x00FF0000) | ((val >> 8) & 0x0000FF00) | (val >> (8 * 3)))
#define SWAP_16(val) ((val << 8) | (val >> 8))

} // namespace LC3_Sim
