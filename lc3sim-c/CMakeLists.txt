cmake_minimum_required(VERSION 3.10)
project(lc3sim-c
    DESCRIPTION "lc3sim-c project"
)

set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")
set(OPTIMIZE_COMPILE_OPTION -O2)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lc3os.c
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lc3os.obj
        COMMAND xxd -i lc3os.obj > ${CMAKE_CURRENT_BINARY_DIR}/lc3os.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating lc3os.c"
    )

ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lc3os32.c
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lc3os32.obj
        COMMAND xxd -i lc3os32.obj > ${CMAKE_CURRENT_BINARY_DIR}/lc3os32.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating lc3os32.c"
    )
    
set(SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/lc3os.c
    ${CMAKE_CURRENT_BINARY_DIR}/lc3os32.c
    vm.h
    vm.c
    )

function(SetOptionts a_TargetName a_Definitions)
    target_compile_definitions(${a_TargetName} PRIVATE ${a_Definitions})
    target_compile_options(${a_TargetName} PRIVATE ${OPTIMIZE_COMPILE_OPTION} -Wall -g --std=c11)
    set_target_properties(${a_TargetName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")
endfunction()

set(CMAKE_C_COMPILER gcc)

# 16 bit
add_executable(lc3sim-c16 
    ${SOURCES}
    main.c
    )
SetOptionts(lc3sim-c16 LC3_16BIT)

add_executable(lc3sim_c16trace 
    ${SOURCES}
    main.c
    )
SetOptionts(lc3sim_c16trace LC3_16BIT)
target_compile_definitions(lc3sim_c16trace PRIVATE LC3_16BIT TRACE)

add_library(liblc3sim_c16 STATIC 
    ${SOURCES}
    )
SetOptionts(liblc3sim_c16 LC3_16BIT)

# 32 bit

add_executable(lc3sim-c32 
    ${SOURCES}
    main.c
    )
SetOptionts(lc3sim-c32 LC3_32BIT)

add_library(liblc3sim_c32 STATIC 
    ${SOURCES}
    )
SetOptionts(liblc3sim_c32 LC3_32BIT)

