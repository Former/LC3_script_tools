cmake_minimum_required(VERSION 3.10)
project(regress_test
    DESCRIPTION "regress_test project"
)

enable_testing()

include(../TestFunc.cmake)

set(source_file_templates
    "stackl_test/*.c"
    "c-testsuite/single-exec/*.c"
    "lcc_regression/*.c"
    )

set(OUT_DIR "build")

# Make source file list
foreach (cur_templete ${source_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_file_list ${cur_list})
endforeach()

# Make obj file list
foreach (cur_file ${src_file_list})
    BuildObjFile(out_file ${cur_file} ${OUT_DIR}) 

    list(APPEND obj_file_list ${out_file})
endforeach()

# Exclude files
set(exclude_src_files_for_lc3sim_c)
set(exclude_src_files_for_lc3sim
    lcc_regression/sort.c
    lcc_regression/spill.c
    lcc_regression/switch.c
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
