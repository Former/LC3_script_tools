cmake_minimum_required(VERSION 3.10)
project(liblcc_prj
	DESCRIPTION "liblcc_prj project"
)

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
	)

add_library(liblcc STATIC 
	${SRCS}
	)

target_compile_options(liblcc PRIVATE ${COMPILE_FLAG} ${EXTRA_COMPILE_OPTIONS})
set_target_properties(liblcc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")

