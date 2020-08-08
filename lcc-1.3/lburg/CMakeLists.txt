cmake_minimum_required(VERSION 3.10)
project(lburg_prj
	DESCRIPTION "lburg_prj project"
)

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
	)

add_executable(lburg
	${SRCS}
	)
target_compile_options(lburg PRIVATE ${COMPILE_FLAG})
set_target_properties(lburg PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")


