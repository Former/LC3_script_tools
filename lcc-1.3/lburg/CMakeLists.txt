cmake_minimum_required(VERSION 3.10)
project(lburg_prj
	DESCRIPTION "lburg_prj project"
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS 
	gram.c
	lburg.c
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

add_executable(lburg
	${SRCS}
	)
target_compile_options(lburg PRIVATE ${COMPILE_FLAG})
#target_link_libraries(lburg m)
set_target_properties(lburg PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")


