cmake_minimum_required(VERSION 3.10)
project(regress_test
    DESCRIPTION "regress_test project"
)

enable_testing()

include(../TestFunc.cmake)

set(OUT_DIR "build")

set(source_16bit_file_templates
    "stackl_test/*.c"
    "c-testsuite/single-exec/*.c"
    "lcc_regression/*.c"
    )

set(source_32bit_file_templates
    "stackl_test/*.c"
    "c-testsuite/single-exec/*.c"
    "lcc_regression/*.c"
    "lcc_regression_32bit/*.c"
    )

# Known errors: this files not compile
set(not_compile_src_files
    c-testsuite/single-exec/00025.c # no strlen
    c-testsuite/single-exec/00040.c # no calloc
    c-testsuite/single-exec/00048.c # no {.name=} in struct
    c-testsuite/single-exec/00049.c # no {.name=} in struct
    c-testsuite/single-exec/00083.c # no define multi arg A(...)
    c-testsuite/single-exec/00084.c # no define multi arg A(...)
    c-testsuite/single-exec/00085.c # no define multi arg A(...)
    c-testsuite/single-exec/00092.c # no int a[] = {5, [2] = 2, 3}
    c-testsuite/single-exec/00094.c # no extern int x; without int x;
    c-testsuite/single-exec/00097.c # no define multi arg A(...)
    c-testsuite/single-exec/00104.c # owerflow
    c-testsuite/single-exec/00108.c # double declare func
    c-testsuite/single-exec/00113.c # float
    c-testsuite/single-exec/00119.c # double
    c-testsuite/single-exec/00123.c # double
    c-testsuite/single-exec/00129.c # #define s s
    c-testsuite/single-exec/00132.c # 00132.c:7: illegal statement termination
    c-testsuite/single-exec/00133.c # 00133.c:8: `1l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00134.c # 00134.c:9: `1l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00135.c # 00135.c:9: `1l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00138.c # lcc unlimit run time
    c-testsuite/single-exec/00144.c # 00144.c:7: `0l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00147.c # no int a[] = {5, [2] = 2, 3}
    c-testsuite/single-exec/00148.c # no int a[] = {5, [2] = 2, 3}
    c-testsuite/single-exec/00149.c # pointer to struct
    c-testsuite/single-exec/00150.c # pointer to struct
    c-testsuite/single-exec/00151.c # no int a[] = {5, [2] = 2, 3}
    c-testsuite/single-exec/00154.c # lcc error?: 00154.c:19: illegal statement termination
    c-testsuite/single-exec/00162.c # void foos(int x[static 5]);
    c-testsuite/single-exec/00163.c # 00163.c:28: illegal statement termination
    c-testsuite/single-exec/00170.c # 00170.c:22: unknown enumeration `efoo'
    c-testsuite/single-exec/00174.c # 00174.c:2 Could not find include file <math.h>
    c-testsuite/single-exec/00175.c # float? 00175.c:15: compiler error in _label--Bad terminal 8225
    c-testsuite/single-exec/00178.c # double
    c-testsuite/single-exec/00179.c # memset
    c-testsuite/single-exec/00180.c # strcpy
    c-testsuite/single-exec/00182.c # 00182.c:187: `0L' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00186.c # sprintf
    c-testsuite/single-exec/00187.c # fopen
    c-testsuite/single-exec/00189.c # fprintf
    c-testsuite/single-exec/00195.c # double
    c-testsuite/single-exec/00201.c # CAT2(a,b) a##b
    c-testsuite/single-exec/00202.c # 00202.c:9 Bad token jim; produced by ##
    c-testsuite/single-exec/00203.c # 00203.c:7: `2147483648LL' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00204.c # float
    c-testsuite/single-exec/00205.c # 00205.c:9: `4194304L' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00206.c # pop_macro
    c-testsuite/single-exec/00207.c # lcc unimplement: char test[argc];
    c-testsuite/single-exec/00209.c # pointer to struct
    c-testsuite/single-exec/00210.c # __attribute__
    c-testsuite/single-exec/00213.c # 00213.c:17: illegal expression
    c-testsuite/single-exec/00214.c # __builtin_expect ?
    c-testsuite/single-exec/00216.c # 00216.c:2: invalid struct field declarations
    c-testsuite/single-exec/00219.c # 00219.c:42: illegal expression
    )

set(exclude_src_16bit_files
    ${not_compile_src_files}
    )

set(exclude_src_32bit_files
    ${not_compile_src_files}
    )

# Make source file list
foreach (cur_templete ${source_16bit_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_16bit_file_list ${cur_list})
endforeach()
list(REMOVE_ITEM src_16bit_file_list ${exclude_src_16bit_files})

foreach (cur_templete ${source_32bit_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_32bit_file_list ${cur_list})
endforeach()
list(REMOVE_ITEM src_32bit_file_list ${exclude_src_32bit_files})


# Make obj file list
foreach (cur_file ${src_16bit_file_list})
    BuildObjFile(out_file ${cur_file} ${LC3_TARGET_LCC_NAME} ${LC3AS} ${CORRECT_EXE} ${OUT_DIR}16) 
    list(APPEND obj_16bit_file_list ${out_file})
endforeach()

foreach (cur_file ${src_32bit_file_list})
    BuildObjFile(out_file ${cur_file} ${LC3_32_TARGET_LCC_NAME} ${LC3AS32} ${CORRECT32_EXE} ${OUT_DIR}32) 
    list(APPEND obj_32bit_file_list ${out_file})
endforeach()

# Known errors 16 bit: Errors when execute
set(exclude_src_files
    c-testsuite/single-exec/00087.c # in output restart os
    c-testsuite/single-exec/00124.c # in output restart os
    c-testsuite/single-exec/00164.c # error! a == b always true, a != b always false 
    c-testsuite/single-exec/00166.c # int owerflow
    c-testsuite/single-exec/00220.c # not work %04x and %ld ....
    lcc_regression/fig14_2.c # int owerflow
    )

set(exclude_src_files_for_lc3sim_c
    ${exclude_src_files}
    )
set(exclude_src_files_for_lc3sim
    ${exclude_src_files}
    lcc_regression/sort.c # in output restart os
    lcc_regression/spill.c # in output restart os
    lcc_regression/switch.c # in output restart os
    
    c-testsuite/single-exec/00181.c # unlimit time exec 
    c-testsuite/single-exec/00215.c # unlimit time exec 
    )

# Config test 16 bit
list(LENGTH obj_16bit_file_list obj_16bit_file_count)
math(EXPR obj_16bit_file_count "${obj_16bit_file_count} - 1")
foreach (index RANGE 0 ${obj_16bit_file_count})
    list(GET obj_16bit_file_list ${index} cur_obj_file)
    list(GET src_16bit_file_list ${index} cur_src_file)

    list(FIND exclude_src_files_for_lc3sim_c ${cur_src_file} find_src_file)
    if (${find_src_file} EQUAL -1)
        AddRegressTest(${LC3SIM_C16} ${cur_obj_file} ${cur_src_file} "sim16" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
        AddRegressTest(${LC3SIM_CPP16} ${cur_obj_file} ${cur_src_file} "sim_cpp16" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    endif()

    list(FIND exclude_src_files_for_lc3sim ${cur_src_file} find_src_file)
    if (${find_src_file} EQUAL -1)
        AddRegressTest(${LC3SIM} ${cur_obj_file} ${cur_src_file} "def16" ${DEFAULT_OUT} ${TYPE_OUT_FILE})
    endif()
endforeach()


# Known errors 32 bit: Errors when execute
set(exclude_src_files_for_lc3sim_c32
    c-testsuite/single-exec/00087.c # in output restart os
    c-testsuite/single-exec/00124.c # in output restart os
    c-testsuite/single-exec/00164.c # error! a == b always true, a != b always false 
    c-testsuite/single-exec/00220.c # not work %04x and %ld ....
    stackl_test/test3.c # COMP broken z=-42406
    )

# Config test 32 bit
list(LENGTH obj_32bit_file_list obj_32bit_file_count)
math(EXPR obj_32bit_file_count "${obj_32bit_file_count} - 1")
foreach (index RANGE 0 ${obj_32bit_file_count})
    list(GET obj_32bit_file_list ${index} cur_obj_file)
    list(GET src_32bit_file_list ${index} cur_src_file)

    list(FIND exclude_src_files_for_lc3sim_c32 ${cur_src_file} find_src_file)
    if (${find_src_file} EQUAL -1)
        AddRegressTest(${LC3SIM_C32} ${cur_obj_file} ${cur_src_file} "sim32" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
        AddRegressTest(${LC3SIM_CPP32} ${cur_obj_file} ${cur_src_file} "sim_cpp32" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    endif()
endforeach()
