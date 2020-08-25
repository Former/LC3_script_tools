cmake_minimum_required(VERSION 3.10)
project(unittest_sim_cpp
    DESCRIPTION "unittest_sim_cpp project"
)

enable_testing()

include_directories(".")
include_directories("../../../lc3sim_cpp")

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

add_executable(unittest_sim_cpp_16 ${src_16bit_file_list} ../main.cpp)
ConfigTestExe(unittest_sim_cpp_16  liblc3sim_cpp16 LC3_16BIT)

add_executable(unittest_sim_cpp_32 ${src_32bit_file_list} ../main.cpp)
ConfigTestExe(unittest_sim_cpp_32 liblc3sim_cpp32 LC3_32BIT)


