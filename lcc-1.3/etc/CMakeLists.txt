cmake_minimum_required(VERSION 3.10)
project(lcc_prj
	DESCRIPTION "lcc_prj project"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS 
	lc3.c
	lcc.c
	)

set(BASEDIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")
set(PATHSEP /)
message("INSTALL_DIR = ${INSTALL_DIR}")

set(COMPILE_FLAG
	-g
	)

add_executable(lcc
	${SRCS}
	)
target_compile_options(lcc PRIVATE ${COMPILE_FLAG} ${EXTRA_COMPILE_OPTIONS})
set_target_properties(lcc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")

target_compile_definitions(lcc PRIVATE LCCDIR="${INSTALL_DIR}${PATHSEP}" PATHSEP="${PATHSEP}" BASEDIR="${BASEDIR}${PATHSEP}")

