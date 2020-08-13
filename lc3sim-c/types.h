//
//  Created by Alexei Bezborodov on 13.08.2020.
//  Copyright © 2020 Alexei Bezborodov. All rights reserved.
//

#pragma once

#include <stdint.h>

#ifdef LC3_32BIT

typedef uint32_t lc3_register_type;
typedef uint32_t lc3_mem_addres_type;

#define LC3_MAX_MEMORY_ADDRES (2*UINT16_MAX) // may be up to UINT32_MAX

#else // LC3_16BIT

typedef uint16_t lc3_register_type;
typedef uint16_t lc3_mem_addres_type;

#define LC3_MAX_MEMORY_ADDRES UINT16_MAX

#endif

#define LC3_SIGN_BIT_INDEX (sizeof(lc3_register_type) * 8 - 1)
#define LC3_STATUS_BIT_INDEX (sizeof(lc3_register_type) * 8 - 1)
