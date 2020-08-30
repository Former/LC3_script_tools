// Copyright 2020 by Alexei Bezborodov <AlexeiBv@narod.ru>

#pragma once 

#if defined(LC3_64BIT_WIDE)
    extern unsigned char lc3os64w_obj[];
    extern unsigned int lc3os64w_obj_len;
    #define lc3os_bin_data lc3os64w_obj
    #define lc3os_bin_data_len lc3os64w_obj_len
#elif defined(LC3_32BIT)
    extern unsigned char lc3os32_obj[];
    extern unsigned int lc3os32_obj_len;
    #define lc3os_bin_data lc3os32_obj
    #define lc3os_bin_data_len lc3os32_obj_len
#elif defined(LC3_32BIT_WIDE)
    extern unsigned char lc3os32w_obj[];
    extern unsigned int lc3os32w_obj_len;
    #define lc3os_bin_data lc3os32w_obj
    #define lc3os_bin_data_len lc3os32w_obj_len
#else
    extern unsigned char lc3os16_obj[];
    extern unsigned int lc3os16_obj_len;
    #define lc3os_bin_data lc3os16_obj
    #define lc3os_bin_data_len lc3os16_obj_len
#endif
