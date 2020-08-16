enable_testing()

include_directories("gtest")

include_directories("../../lc3sim-c")
include_directories(".")

set(OPTIMIZE_COMPILE_OPTION -O2)

add_library(libgtest STATIC 
    gtest/gtest-all.cc
    )

set(test_index 0)

function(AddTest a_TestSourceFile a_Lib a_Definitions)
    math(EXPR test_index "${test_index} + 1")
    set(test_index ${test_index} PARENT_SCOPE)
    
    get_filename_component(out_file_name ${a_TestSourceFile} NAME)
    set(test_target_name unittest${test_index}_${out_file_name})
    
    add_executable(${test_target_name} ${a_TestSourceFile} main.cpp)
    target_compile_definitions(${test_target_name} PRIVATE ${a_Definitions})
    target_compile_options(${test_target_name} PRIVATE ${OPTIMIZE_COMPILE_OPTION} -Wall -g --std=c11)
    target_link_libraries(${test_target_name} libgtest ${a_Lib} libpthread)
    add_test(unittest_${test_target_name} ${test_target_name})
endfunction()

AddTest(test_lc3sim-c.cpp liblc3sim-c16 LC3_16BIT)
AddTest(test_lc3sim-c.cpp liblc3sim-c32 LC3_32BIT)


