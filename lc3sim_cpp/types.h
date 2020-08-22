// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

#pragma once

#include <stdint.h>

namespace LC3_Sim
{

#ifdef LC3_32BIT

typedef uint32_t LC3_RegisterType;
typedef uint32_t LC3MemAddressType;

#define LC3_MAX_MEMORY_ADDRESS (2*UINT16_MAX) // may be up to UINT32_MAX

#else // LC3_16BIT

typedef uint16_t LC3_RegisterType;
typedef uint16_t LC3MemAddressType;

#define LC3_MAX_MEMORY_ADDRESS UINT16_MAX

#endif

#define LC3_SIGN_BIT_INDEX (sizeof(LC3_Sim::LC3_RegisterType) * 8 - 1)
#define LC3_STATUS_BIT_INDEX (sizeof(LC3_Sim::LC3_RegisterType) * 8 - 1)

} // namespace LC3_Sim