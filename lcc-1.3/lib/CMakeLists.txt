cmake_minimum_required(VERSION 3.10)
project(liblcc_prj
	DESCRIPTION "liblcc_prj project"
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS 
	assert.c
	bbexit.c
	yynull.c
	)

set(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(INSTALL_DIR ${CMAKE_BINARY_DIR})
set(PATHSEP /)

set(COMPILE_FLAG
	-g
	-Wall
#	-DLCCDIR='"${LCCDIR}${PATHSEP}"'
#	-DPATHSEP='"${PATHSEP}"'
#	-DBASEDIR='"${BASEDIR}${PATHSEP}"'
#	${EXTRAFLAGS}
	)

add_library(liblcc STATIC 
	${SRCS}
	)

#add_executable(lc3pp
	#${SRCS}
	#)
target_compile_options(liblcc PRIVATE ${COMPILE_FLAG})
#target_link_libraries(lc3pp m)
set_target_properties(liblcc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")

