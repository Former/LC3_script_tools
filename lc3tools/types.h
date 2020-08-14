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
 * Filename:	    symbol.h
 * History:
 *		Copyright notices and Gnu Public License marker added.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#ifdef LC3_32BIT

typedef uint32_t lc3_register_type;
#define LC3_SWAP swap32
#define LC3_CODE_MASK 0xFFFFFFFF
//typedef uint32_t lc3_mem_addres_type;

//#define LC3_MAX_MEMORY_ADDRES (2*UINT16_MAX) // may be up to UINT32_MAX

#else // LC3_16BIT

typedef uint16_t lc3_register_type;
#define LC3_SWAP swap16
#define LC3_CODE_MASK 0x0000FFFF
//typedef uint16_t lc3_mem_addres_type;

//#define LC3_MAX_MEMORY_ADDRES UINT16_MAX

#endif // LC3_32BIT and LC3_16BIT


#define LC3_REG_BIT_COUNT (sizeof(lc3_register_type) * 8)
//#define LC3_SIGN_BIT_INDEX (sizeof(lc3_register_type) * 8 - 1)
//#define LC3_STATUS_BIT_INDEX (sizeof(lc3_register_type) * 8 - 1)

#endif //TYPES_H
