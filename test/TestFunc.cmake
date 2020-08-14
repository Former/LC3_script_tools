set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")

set(LCC ${INSTALL_DIR}/lcc) 
set(LC3AS ${INSTALL_DIR}/lc3as) 
set(LC3AS32 ${INSTALL_DIR}/lc3as32) 
set(LC3SIM ${INSTALL_DIR}/lc3sim) 
set(LC3SIM_C16 ${INSTALL_DIR}/lc3sim-c16) 
set(LC3SIM_C32 ${INSTALL_DIR}/lc3sim-c32) 

set(CORRECT_EXE ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj_file)
set(CORRECT32_EXE ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj32_file)

set(LC3_TARGET_LCC_NAME "lc3") 
set(LC3_32_TARGET_LCC_NAME "lc3_32bit") 

set(DEFAULT_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../default_out) 

set(TYPE_OUT_STDOUT "stdout")
set(TYPE_OUT_FILE "file")

function(BuildObjFile a_OutObjFile a_InputFile a_TargetName a_AsmExe a_CorrectExe a_OutBuildDir)
    set(raw_template_out_file
        ${CMAKE_CURRENT_BINARY_DIR}/${a_OutBuildDir}/${a_InputFile}
        )

    get_filename_component(out_file_dir ${raw_template_out_file} DIRECTORY)
    get_filename_component(out_file_name ${raw_template_out_file} NAME)
    get_filename_component(out_file_name_we ${raw_template_out_file} NAME_WE)

    set(template_out_file 
        ${out_file_dir}/${out_file_name_we}
        )

    set(obj_file ${template_out_file}.obj)
    set(obj_correct_file ${template_out_file}_correct.obj)
    set(${a_OutObjFile} ${obj_correct_file} PARENT_SCOPE)

    add_custom_command(
        OUTPUT ${obj_correct_file}
        COMMAND mkdir -p ${out_file_dir}
        COMMAND ${LCC} -target=${a_TargetName} -L ${CMAKE_CURRENT_SOURCE_DIR}/${a_InputFile} -o ${template_out_file}
        COMMAND ${a_AsmExe} ${template_out_file}.asm
        COMMAND ${a_CorrectExe} ${obj_file} ${obj_correct_file}
        #WORKING_DIRECTORY ${out_file_dir}
        DEPENDS lcc lc3as lc3as32 rcc cpp ${CMAKE_CURRENT_SOURCE_DIR}/${a_InputFile}
        COMMENT "Compile ${a_OutBuildDir}/${a_InputFile}"
    )

    set(cur_target_name ${a_OutBuildDir}_${out_file_name})
    add_custom_target(${cur_target_name} ALL DEPENDS ${obj_correct_file})
endfunction()

function(BuildObjFiles a_OutObjFileList a_InputFileList a_TargetName a_AsmExe a_CorrectExe a_OutBuildDir)
    set(out_list)
    foreach(cur_file ${a_InputFileList})
        BuildObjFile(out_file ${cur_file} ${a_TargetName} ${a_AsmExe} ${a_CorrectExe} ${a_OutBuildDir}) 

        list(APPEND out_list ${out_file})
    endforeach()

    set(${a_OutObjFileList} ${out_list} PARENT_SCOPE)
endfunction()

function(AndRegressTest a_SimExe a_ObjFile a_SourceFile a_AppendForNameTempFiles a_DefaultOutFile a_TypeOut)
    add_test(NAME test_${a_AppendForNameTempFiles}__${a_SourceFile}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../run_regress_test 
            ${a_SimExe}
            ${a_ObjFile}
            ${a_AppendForNameTempFiles}
            ${CMAKE_CURRENT_SOURCE_DIR}/${a_SourceFile}.in
            ${CMAKE_CURRENT_SOURCE_DIR}/${a_SourceFile}.expected
            ${a_DefaultOutFile} 
            ${a_TypeOut}
        )
endfunction()
