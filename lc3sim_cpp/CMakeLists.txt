cmake_minimum_required(VERSION 3.10)
project(lc3sim_cpp
    DESCRIPTION "lc3sim_cpp project"
)

set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")
set(OPTIMIZE_COMPILE_OPTION -O3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

function(GenOS a_OsFileName)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${a_OsFileName}.c
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${a_OsFileName}.obj
        COMMAND xxd -i ${a_OsFileName}.obj > ${CMAKE_CURRENT_BINARY_DIR}/${a_OsFileName}.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating ${a_OsFileName}.c"
    )
endfunction()

GenOS(lc3os16)
GenOS(lc3os32)
GenOS(lc3os32w)
GenOS(lc3os64w)

set(SOURCES_LC3SIM_CPP
    ${CMAKE_CURRENT_BINARY_DIR}/lc3os16.c
    ${CMAKE_CURRENT_BINARY_DIR}/lc3os32.c
    ${CMAKE_CURRENT_BINARY_DIR}/lc3os32w.c
    ${CMAKE_CURRENT_BINARY_DIR}/lc3os64w.c
    lc3sim.h
    sim_types.h
    instr_config.h
    instr_converter.h
    instr_parser.h
    instr_maker.h
    lc3sim.cpp
    )

function(SetOptionts a_TargetName a_Definitions)
    target_compile_definitions(${a_TargetName} PRIVATE ${a_Definitions})
    target_compile_options(${a_TargetName} PRIVATE ${OPTIMIZE_COMPILE_OPTION} -Wall -g)
    set_target_properties(${a_TargetName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")
endfunction()

function(MakeSim a_TargetBaseName a_Definition)
    add_library(lib${a_TargetBaseName} STATIC 
        ${SOURCES_LC3SIM_CPP}
        )
    SetOptionts(lib${a_TargetBaseName} ${a_Definition})

    add_executable(${a_TargetBaseName} 
        main.cpp
        )
    SetOptionts(${a_TargetBaseName} ${a_Definition})
    target_link_libraries(${a_TargetBaseName} lib${a_TargetBaseName})

    add_executable(${a_TargetBaseName}trace 
        ${SOURCES_LC3SIM_CPP}
        main.cpp
        )
    SetOptionts(${a_TargetBaseName}trace ${a_Definition})
    target_compile_definitions(${a_TargetBaseName}trace PRIVATE ${a_Definition} TRACE)
endfunction()

MakeSim(lc3sim_cpp16 LC3_16BIT)
MakeSim(lc3sim_cpp32 LC3_32BIT)
MakeSim(lc3sim_cpp32w LC3_32BIT_WIDE)
MakeSim(lc3sim_cpp64w LC3_64BIT_WIDE)
