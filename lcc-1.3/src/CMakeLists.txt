cmake_minimum_required(VERSION 3.10)
project(rcc_prj
	DESCRIPTION "rcc_prj project"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRCS 
	alloc.c
	enode.c
	inits.c
	list.c
	simp.c
	sym.c
	bind.c
	error.c
	input.c
	trace.c
	bytecode.c
	event.c
	null.c
	stab.c
	tree.c
	dag.c
	expr.c
	output.c
	stmt.c
	types.c
	gen.c
	lc3_stab.c
	prof.c
	string.c
	decl.c
	init.c
	lex.c
	profio.c
	symbolic.c

	dagcheck.c
	lc3.c
	lc3_32bit.c
	#lc3dtu.c
	#sparc.c
	#x86.c
	#x86linux.c
	)

set(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")
set(PATHSEP /)

add_library(librcc STATIC 
	${SRCS}
	)
target_compile_options(librcc PRIVATE ${COMPILE_FLAG} ${EXTRA_COMPILE_OPTIONS})

set(GEN_FILES 
	dagcheck
	lc3
	lc3_32bit
	#lc3dtu
	#sparc
	#x86
	#x86linux
	)

foreach(GEN_FILE ${GEN_FILES})
	set(GEN_FILE_C ${GEN_FILE}.c)
	set(GEN_FILE_MD ${GEN_FILE}.md)

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${GEN_FILE_C}
		PRE_BUILD
		COMMAND ${INSTALL_DIR}/lburg ${GEN_FILE_MD} ${GEN_FILE_C}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS lburg
		COMMENT "Create ${GEN_FILE_C}"
		)

	add_custom_target(opcode_defs_${GEN_FILE} DEPENDS ${GEN_FILE_C})
	add_dependencies(librcc opcode_defs_${GEN_FILE})
endforeach()

set(COMPILE_FLAG
	-g
	)

add_executable(rcc
	main.c
	)
target_compile_options(rcc PRIVATE ${COMPILE_FLAG} ${EXTRA_COMPILE_OPTIONS})
set_target_properties(rcc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}/")

target_link_libraries(rcc librcc)

