cmake_minimum_required(VERSION 3.10)
project(unit_test
    DESCRIPTION "unit_test project"
)

enable_testing()

set(BIN_DIR "${CMAKE_BINARY_DIR}/")

set(OPTIMIZE_COMPILE_OPTION -O0)

macro(ConfigTestExe a_TestName a_Lib a_Definitions)
    target_compile_definitions(${a_TestName} PRIVATE ${a_Definitions})
    target_compile_options(${a_TestName} PRIVATE ${OPTIMIZE_COMPILE_OPTION} -Wall -g)
    target_link_libraries(${a_TestName} libgtest ${a_Lib} pthread m)
    set_target_properties(${a_TestName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
    
    add_test(run_${a_TestName} ${BIN_DIR}${a_TestName})
endmacro()

include_directories(".")

add_library(libgtest STATIC 
    gtest/gtest-all.cc
    )

add_subdirectory(lc3sim-c)
add_subdirectory(lc3sim_cpp)


