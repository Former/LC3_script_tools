cmake_minimum_required(VERSION 3.10)
project(unit_test
    DESCRIPTION "unit_test project"
)

enable_testing()

include_directories("gtest")

include_directories("../../lc3sim-c")
include_directories(".")

set(OPTIMIZE_COMPILE_OPTION -O2)

add_library(libgtest STATIC 
    gtest/gtest-all.cc
    )

set(source_16bit_file_templates
    "lc3sim-c/*.cpp"
    )

set(source_32bit_file_templates
    "lc3sim-c/*.cpp"
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

macro(AddTest a_TestName a_FileList a_Lib a_Definitions)
    add_executable(${a_TestName} ${a_FileList} main.cpp)
    target_compile_definitions(${a_TestName} PRIVATE ${a_Definitions})
    target_compile_options(${a_TestName} PRIVATE ${OPTIMIZE_COMPILE_OPTION} -Wall -g)
    target_link_libraries(${a_TestName} libgtest ${a_Lib} pthread m)
    set_target_properties(${a_TestName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
    
    add_test(run_${a_TestName} ${BIN_DIR}${a_TestName})
endmacro()

AddTest("unittest_16" ${src_16bit_file_list} liblc3sim_c16 LC3_16BIT)
AddTest("unittest_32" ${src_32bit_file_list} liblc3sim_c32 LC3_32BIT)


