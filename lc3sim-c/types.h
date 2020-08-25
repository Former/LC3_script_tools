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
#define LC3_SWAP SWAP_32

#define lc3os_bin_data lc3os32_obj
#define lc3os_bin_data_len lc3os32_obj_len

#else // LC3_16BIT

typedef uint16_t lc3_register_type;
typedef uint16_t lc3_mem_addres_type;

#define LC3_MAX_MEMORY_ADDRES UINT16_MAX
#define LC3_SWAP SWAP_16

#define lc3os_bin_data lc3os_obj
#define lc3os_bin_data_len lc3os_obj_len

#endif

#define LC3_SIGN_BIT_INDEX (sizeof(lc3_register_type) * 8 - 1)
#define LC3_STATUS_BIT_INDEX (sizeof(lc3_register_type) * 8 - 1)

#define SWAP_32(val) ((val << (8 * 3)) | ((val << 8) & 0x00FF0000) | ((val >> 8) & 0x0000FF00) | (val >> (8 * 3)))
#define SWAP_16(val) ((val << 8) | (val >> 8))
