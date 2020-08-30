cmake_minimum_required(VERSION 3.10)
project(unittest_sim_cpp
    DESCRIPTION "unittest_sim_cpp project"
)

enable_testing()

include_directories(".")
include_directories("../../../lc3sim_cpp")

set(source_file_templates
    "*.cpp"
    )

foreach (cur_templete ${source_file_templates})
    file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

    list(APPEND src_file_list ${cur_list})
endforeach()

add_executable(unittest_sim_cpp_16 ${src_file_list} ../main.cpp)
ConfigTestExe(unittest_sim_cpp_16  liblc3sim_cpp16 LC3_16BIT)

add_executable(unittest_sim_cpp_32 ${src_file_list} ../main.cpp)
ConfigTestExe(unittest_sim_cpp_32 liblc3sim_cpp32 LC3_32BIT)

add_executable(unittest_sim_cpp_32w ${src_file_list} ../main.cpp)
ConfigTestExe(unittest_sim_cpp_32w liblc3sim_cpp32w LC3_32BIT_WIDE)

add_executable(unittest_sim_cpp_64w ${src_file_list} ../main.cpp)
ConfigTestExe(unittest_sim_cpp_64w liblc3sim_cpp64w LC3_64BIT_WIDE)
