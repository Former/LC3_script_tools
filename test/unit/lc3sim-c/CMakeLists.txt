cmake_minimum_required(VERSION 3.10)
project(unittest_sim_c
    DESCRIPTION "unittest_sim_c project"
)

enable_testing()

include_directories(".")
include_directories("../../../lc3sim-c")

set(OPTIMIZE_COMPILE_OPTION -O2)

set(source_16bit_file_templates
    "*.cpp"
    )

set(source_32bit_file_templates
    "*.cpp"
    )

foreach (cur_templete ${source_16bit_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_16bit_file_list ${cur_list})
endforeach()

foreach (cur_templete ${source_32bit_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_32bit_file_list ${cur_list})
endforeach()

set(BIN_DIR "${CMAKE_BINARY_DIR}/")

AddTest("unittest_sim_c_16" ${src_16bit_file_list} liblc3sim_c16 LC3_16BIT)
AddTest("unittest_sim_c_32" ${src_32bit_file_list} liblc3sim_c32 LC3_32BIT)


