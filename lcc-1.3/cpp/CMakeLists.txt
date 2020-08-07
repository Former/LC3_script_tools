cmake_minimum_required(VERSION 3.10)
project(cpp_prj
	DESCRIPTION "cpp_prj project"
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS 
	cpp.c
	getopt.c
	include.c
	macro.c
	tokens.c
	eval.c
	hideset.c
	lex.c
	nlist.c
	unix.c
	)

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

add_executable(cpp
	${SRCS}
	)
target_compile_options(cpp PRIVATE ${COMPILE_FLAG})
#target_link_libraries(cpp m)
set_target_properties(cpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")


