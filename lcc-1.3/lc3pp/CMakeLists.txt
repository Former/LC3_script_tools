cmake_minimum_required(VERSION 3.10)
project(lc3pp_prj
	DESCRIPTION "lc3pp_prj project"
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")
set(PATHSEP /)

set(COMPILE_FLAG
	-g
#	-DLCCDIR='"${LCCDIR}${PATHSEP}"'
#	-DPATHSEP='"${PATHSEP}"'
#	-DBASEDIR='"${BASEDIR}${PATHSEP}"'
#	${EXTRAFLAGS}
	)

add_executable(lc3pp
	lc3pp.c
	)
target_compile_options(lc3pp PRIVATE ${COMPILE_FLAG})
set_target_properties(lc3pp PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")

add_executable(SourcePaste
	SourcePaste.c
	)
target_compile_options(SourcePaste PRIVATE ${COMPILE_FLAG})
set_target_properties(SourcePaste PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")

