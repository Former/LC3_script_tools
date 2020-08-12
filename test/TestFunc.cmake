set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")

set(LCC ${INSTALL_DIR}/lcc) 
set(LC3AS ${INSTALL_DIR}/lc3as) 
set(LC3SIM ${INSTALL_DIR}/lc3sim) 
set(LC3SIM_C ${INSTALL_DIR}/lc3sim-c) 

set(DEFAULT_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../default_out) 

set(TYPE_OUT_STDOUT "stdout")
set(TYPE_OUT_FILE "file")

function(BuildObjFile a_OutObjFile a_InputFile a_OutBuildDir)
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
        COMMAND ${LCC} ${CMAKE_CURRENT_SOURCE_DIR}/${a_InputFile} -o ${template_out_file}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj_file ${obj_file} ${obj_correct_file}
        DEPENDS lcc lc3as rcc cpp
        COMMENT "Compile ${a_InputFile}"
    )

    set(cur_target_name ${a_OutBuildDir}_${out_file_name})
    add_custom_target(${cur_target_name} ALL DEPENDS ${obj_correct_file})
endfunction()

function(BuildObjFiles a_OutObjFileList a_InputFileList a_OutBuildDir)
    set(out_list)
    foreach(cur_file ${a_InputFileList})
        BuildObjFile(out_file ${cur_file} ${a_OutBuildDir}) 

        list(APPEND out_list ${out_file})
    endforeach()

    set(${a_OutObjFileList} ${out_list} PARENT_SCOPE)
endfunction()

function(AndRegressTest a_SimExe a_ObjFile a_SourceFile a_AppendForNameTempFiles a_DefaultOutFile a_TypeOut)
    add_test(NAME test_${a_SourceFile}_${a_AppendForNameTempFiles} 
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
