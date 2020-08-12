cmake_minimum_required(VERSION 3.10)
project(regress_test
    DESCRIPTION "regress_test project"
)

enable_testing()

include(../TestFunc.cmake)

set(OUT_DIR "build")

set(source_file_templates
    "stackl_test/*.c"
    "c-testsuite/single-exec/*.c"
    "lcc_regression/*.c"
    )

set(exclude_src_files
    c-testsuite/single-exec/00132.c # 00132.c:7: illegal statement termination
    c-testsuite/single-exec/00133.c # 00133.c:8: `1l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00134.c # 00134.c:9: `1l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00135.c # 00135.c:9: `1l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00138.c # lcc unlimit run time
    c-testsuite/single-exec/00144.c # 00144.c:7: `0l' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00154.c # lcc error?: 00154.c:19: illegal statement termination
    c-testsuite/single-exec/00163.c # 00163.c:28: illegal statement termination
    c-testsuite/single-exec/00170.c # 00170.c:22: unknown enumeration `efoo'
    c-testsuite/single-exec/00174.c # 00174.c:2 Could not find include file <math.h>
    c-testsuite/single-exec/00175.c # float? 00175.c:15: compiler error in _label--Bad terminal 8225
    c-testsuite/single-exec/00182.c # 00182.c:187: `0L' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00202.c # 00202.c:9 Bad token jim; produced by ##
    c-testsuite/single-exec/00203.c # 00203.c:7: `2147483648LL' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00205.c # 00205.c:9: `4194304L' is a preprocessing number but an invalid integer constant
    c-testsuite/single-exec/00207.c # lcc unimplement: char test[argc];
    c-testsuite/single-exec/00213.c # 00213.c:17: illegal expression
    c-testsuite/single-exec/00216.c # 00216.c:2: invalid struct field declarations
    c-testsuite/single-exec/00219.c # 00219.c:42: illegal expression
    )

# Make source file list
foreach (cur_templete ${source_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_file_list ${cur_list})
endforeach()
list(REMOVE_ITEM src_file_list ${exclude_src_files})

# Make obj file list
foreach (cur_file ${src_file_list})
    BuildObjFile(out_file ${cur_file} ${OUT_DIR}) 

    list(APPEND obj_file_list ${out_file})
endforeach()

# Exclude files
    set(exclude_src_files
    c-testsuite/single-exec/00087.c # in output restart os
    c-testsuite/single-exec/00164.c # error! a == b always true, a != b always false 
    c-testsuite/single-exec/00166.c # int owerflow
    c-testsuite/single-exec/00220.c # not work %04x
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
    )

# Config test
list(LENGTH obj_file_list obj_file_count)
math(EXPR obj_count "${obj_file_count} - 1")
foreach (index RANGE 0 ${obj_count})
    list(GET obj_file_list ${index} cur_obj_file)
    list(GET src_file_list ${index} cur_src_file)

    list(FIND exclude_src_files_for_lc3sim_c ${cur_src_file} find_src_file)
    if(${find_src_file} EQUAL -1)
        AndRegressTest(${LC3SIM_C} ${cur_obj_file} ${cur_src_file} "sim_c" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    endif()

    list(FIND exclude_src_files_for_lc3sim ${cur_src_file} find_src_file)
    if (${find_src_file} EQUAL -1)
        AndRegressTest(${LC3SIM} ${cur_obj_file} ${cur_src_file} "sim" ${DEFAULT_OUT} ${TYPE_OUT_FILE})
    endif()
endforeach()
