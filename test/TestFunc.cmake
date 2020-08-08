set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")

set(LCC ${INSTALL_DIR}/lcc) 
set(LC3AS ${INSTALL_DIR}/lc3as) 
set(LC3SIM ${INSTALL_DIR}/lc3sim) 

set(DEFAULT_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../default_out) 

function(BuildFile a_OutFile a_InputFile a_Oprimization a_Index)
	set(RAW_OUT_FILE
		${CMAKE_CURRENT_BINARY_DIR}/build-O${a_Oprimization}/${a_InputFile}
		)

	get_filename_component(OUT_FILE_DIR ${RAW_OUT_FILE} DIRECTORY)
	get_filename_component(OUT_FILE_NAME ${RAW_OUT_FILE} NAME)
	get_filename_component(OUT_FILE_NAME_WE ${RAW_OUT_FILE} NAME_WE)

	set(OUT_FILE 
		${OUT_FILE_DIR}/${OUT_FILE_NAME_WE}
		)

	set(${a_OutFile} ${OUT_FILE}.obj PARENT_SCOPE)
	
	add_custom_command(
		OUTPUT ${OUT_FILE}.asm
		COMMAND mkdir -p ${OUT_FILE_DIR}
		COMMAND ${LCC} ${CMAKE_CURRENT_SOURCE_DIR}/${a_InputFile} -o ${OUT_FILE}
		DEPENDS lcc lc3as rcc cpp
		COMMENT "Compile ${SRCS_TEST_C_FILE}"
	)

	set(TARGET_NAME ${OUT_FILE_NAME}_${a_Index}_${a_Oprimization})
	add_custom_target(${TARGET_NAME} ALL DEPENDS ${OUT_FILE}.asm)
endfunction()

function(BuildFile_AndRegressTest a_FileName a_Oprimization a_Index)
	BuildFile(OUT_FILE ${a_FileName} ${a_Oprimization} ${a_Index})
	
	add_test(NAME test_${INDEX}_${a_FileName}_${a_Oprimization} 
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../run_regress_test ${LC3SIM} ${OUT_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/${a_FileName}.in ${CMAKE_CURRENT_SOURCE_DIR}/${a_FileName}.expected ${DEFAULT_OUT}
		)
endfunction()

function(BuildRegressTest a_InputFileTemplate)
	file(GLOB SRCS_TEST_C_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${a_InputFileTemplate}) 
	
	set(INDEX 0)
	
	foreach(SRCS_TEST_C_FILE ${SRCS_TEST_C_FILES})
		math(EXPR INDEX "${INDEX} + 1")
		
		BuildFile_AndRegressTest(${SRCS_TEST_C_FILE} 0 ${INDEX})

	endforeach()
endfunction()
