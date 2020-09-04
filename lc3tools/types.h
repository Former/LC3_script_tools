/*									tab:8
 *
 * types.h - types for LC-3 assembler and simulator 16 and 32 bit version
 *
 * "Copyright (c) 2020 by Alexei Bezborodov."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written 
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software,
 * that the files COPYING and NO_WARRANTY are included verbatim with
 * any distribution, and that the contents of the file README are included
 * verbatim as part of a file named README with any distribution.
 * 
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT, 
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT 
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR 
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" 
 * BASIS, AND THE AUTHOR NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
 * UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Alexei Bezborodov
 * Version:	    1
 * Creation Date:   13.08.2020
 * Filename:	    types.h
 * History:
 *		Copyright notices and Gnu Public License marker added.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#if defined(LC3_64BIT_WIDE)

    typedef uint64_t lc3_register_type;
    #define LC3_SWAP SWAP_64
    #define LC3_VALUE_MASK 0xFFFFFFFFFFFFFFFFUL
    #define LC3_ADDR_MASK 0xFFFF
    #define LC3_INSTR_BIT_COUNT 64
    #define LC3_LOAD_REG_BIT_COUNT 32

    #define HANDLES_64_BIT_LONGS_PROPERTY(value) 

    #define CHECK_OUT_OF_RANGE(bits) 0
    #define CHECK_OUT_OF_RANGE_UNSIGNED(bits) 0

#elif defined(LC3_32BIT)

    typedef uint32_t lc3_register_type;
    #define LC3_SWAP SWAP_32
    #define LC3_VALUE_MASK 0xFFFFFFFF
    #define LC3_ADDR_MASK 0xFFFF
    #define LC3_INSTR_BIT_COUNT 16
    #define LC3_LOAD_REG_BIT_COUNT 32

    #define HANDLES_64_BIT_LONGS_PROPERTY(value) 

    #define CHECK_OUT_OF_RANGE(bits) 0
    #define CHECK_OUT_OF_RANGE_UNSIGNED(bits) 0

#elif defined(LC3_32BIT_WIDE)

    typedef uint32_t lc3_register_type;
    #define LC3_SWAP SWAP_32
    #define LC3_VALUE_MASK 0xFFFFFFFF
    #define LC3_ADDR_MASK 0xFFFF
    #define LC3_INSTR_BIT_COUNT 32
    #define LC3_LOAD_REG_BIT_COUNT 32

    #define HANDLES_64_BIT_LONGS_PROPERTY(value) 

    #define CHECK_OUT_OF_RANGE(bits) 0
    #define CHECK_OUT_OF_RANGE_UNSIGNED(bits) 0

#else // LC3_16BIT

    typedef uint16_t lc3_register_type;
    #define LC3_SWAP SWAP_16
    #define LC3_VALUE_MASK 0x0000FFFF
    #define LC3_ADDR_MASK 0xFFFF
    #define LC3_INSTR_BIT_COUNT 16
    #define LC3_LOAD_REG_BIT_COUNT 16

    #define HANDLES_64_BIT_LONGS_PROPERTY(value) \
        do { \
        if (0x10000 > (value) && 0x8000 <= (value)) \
            (value) |= -65536L; \
        } while (0)

    #define CHECK_OUT_OF_RANGE(bits) ((v < -(1L << (bits - 1))) || (v >= (1L << (bits - 1))))
    #define CHECK_OUT_OF_RANGE_UNSIGNED(bits) (v >= (1L << (bits)))

#endif // LC3_32BIT and LC3_16BIT

#define BIT_IN_ONE_BYTE_COUNT 8
#define LC3_REG_BIT_COUNT (sizeof(lc3_register_type) * BIT_IN_ONE_BYTE_COUNT)
#define SWAP_64(val) val //((val << (BIT_IN_ONE_BYTE_COUNT * 3)) | ((val << BIT_IN_ONE_BYTE_COUNT) & 0x00FF0000) | ((val >> BIT_IN_ONE_BYTE_COUNT) & 0x0000FF00) | (val >> (BIT_IN_ONE_BYTE_COUNT * 3)))
#define SWAP_32(val) (((val << (BIT_IN_ONE_BYTE_COUNT * 3)) & 0xFF000000) | ((val << BIT_IN_ONE_BYTE_COUNT) & 0x00FF0000) | ((val >> BIT_IN_ONE_BYTE_COUNT) & 0x0000FF00) | ((val >> (BIT_IN_ONE_BYTE_COUNT * 3)) & 0x000000FF))
#define SWAP_16(val) ((val << BIT_IN_ONE_BYTE_COUNT) | (val >> BIT_IN_ONE_BYTE_COUNT))

#endif //TYPES_H
