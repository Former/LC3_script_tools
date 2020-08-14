cmake_minimum_required(VERSION 3.10)
project(lc3tools
    DESCRIPTION "lc3tools project"
    LANGUAGES C
)

set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")
set(OPTIMIZE_COMPILE_OPTION -O2)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# lc3as lc3as32
FIND_PACKAGE(FLEX REQUIRED)
if (FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.lc3.c
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lc3.f
        COMMAND ${FLEX_EXECUTABLE} 
            -i -Plc3 ${CMAKE_CURRENT_SOURCE_DIR}/lc3.f
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating lex.lc3.c"
    )
endif(FLEX_FOUND)

add_library(libasm_symbol STATIC 
     symbol.c
     symbol.h
     )
target_compile_options(libasm_symbol PRIVATE -g -Wall)

set(SOURCES_ASM 
     ${CMAKE_CURRENT_SOURCE_DIR}/lex.lc3.c
     )

function(add_asm_exe a_ExeName)
     add_executable(${a_ExeName} 
          ${SOURCES_ASM}
          )
     
     target_compile_definitions(${a_ExeName} PRIVATE ONLY_OBJ_FILE)
     target_compile_options(${a_ExeName} PRIVATE -g ${OPTIMIZE_COMPILE_OPTION})
     target_link_libraries(${a_ExeName} libasm_symbol)
     set_target_properties(${a_ExeName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")
endfunction()

add_asm_exe(lc3as)
add_asm_exe(lc3as32)
target_compile_definitions(lc3as32 PRIVATE LC3_32BIT)

# lc3Convert
FIND_PACKAGE(FLEX REQUIRED)
if (FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.lc3convert.c
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lc3convert.f
        COMMAND ${FLEX_EXECUTABLE} 
            -i -Plc3convert ${CMAKE_CURRENT_SOURCE_DIR}/lc3convert.f
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating lex.lc3convert.c"
    )
endif(FLEX_FOUND)

set(SOURCES_COVERT
     ${CMAKE_CURRENT_SOURCE_DIR}/lex.lc3convert.c
     )

add_executable(lc3convert 
     ${SOURCES_COVERT}
     )

target_compile_options(lc3convert PRIVATE -g ${OPTIMIZE_COMPILE_OPTION})
set_target_properties(lc3convert PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")

# lc3sim
add_library(libsim_symbol STATIC 
     symbol.c
     symbol.h
     )
target_compile_definitions(libsim_symbol PRIVATE MAP_LOCATION_TO_SYMBOL)
target_compile_options(libsim_symbol PRIVATE -g -Wall ${OPTIMIZE_COMPILE_OPTION})

set(SIM_FILES 
     lc3sim.c
     lc3.def
     lc3sim.h
     symbol.h
     )

add_executable(lc3sim
     ${SIM_FILES}
     )
target_link_libraries(lc3sim curses libsim_symbol)
target_compile_definitions(lc3sim PRIVATE INSTALL_DIR="${INSTALL_DIR}" MAP_LOCATION_TO_SYMBOL)
target_compile_options(lc3sim PRIVATE -g -Wall ${OPTIMIZE_COMPILE_OPTION})
set_target_properties(lc3sim PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")

# lc3sym-tk
set(SED /bin/sed)
set(WISH /usr/bin/wish)
set(CHMOD /bin/chmod)
set(CODE_FONT "{{Lucida Console} 11 bold}")
set(BUTTON_FONT "{{Lucida Console} 10 normal}")
set(CONSOLE_FONT "{{Lucida Console} 10 bold}")

ADD_CUSTOM_COMMAND(
     OUTPUT ${INSTALL_DIR}/lc3sim-tk
     SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lc3sim-tk.def
     COMMAND ${SED} -e 's @@WISH@@ ${WISH} g' 
          -e 's*@@LC3_SIM@@*"${INSTALL_DIR}/lc3sim"*g' 
          -e 's!@@CODE_FONT@@!${CODE_FONT}!g' 
          -e 's!@@BUTTON_FONT@@!${BUTTON_FONT}!g' 
          -e 's!@@CONSOLE_FONT@@!${CONSOLE_FONT}!g' 
          ${CMAKE_CURRENT_SOURCE_DIR}/lc3sim-tk.def > ${INSTALL_DIR}/lc3sim-tk
     COMMAND ${CHMOD} u+x ${INSTALL_DIR}/lc3sim-tk
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     COMMENT "Generating lex.lc3.c"
)

add_custom_target(lc3sim-tk_exe ALL DEPENDS ${INSTALL_DIR}/lc3sim-tk)

# lc3os

ADD_CUSTOM_COMMAND(
     OUTPUT ${INSTALL_DIR}/lc3os.obj
     SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lc3os.asm
     COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/lc3os.asm ${INSTALL_DIR}/lc3os.asm
     COMMAND lc3as ${INSTALL_DIR}/lc3os.asm
     WORKING_DIRECTORY ${INSTALL_DIR}
     COMMENT "Generating lc3os.obj"
)

add_custom_target(lc3os_obj ALL DEPENDS ${INSTALL_DIR}/lc3os.obj)
