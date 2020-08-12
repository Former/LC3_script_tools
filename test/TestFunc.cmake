set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")

set(LCC ${INSTALL_DIR}/lcc) 
set(LC3AS ${INSTALL_DIR}/lc3as) 
set(LC3SIM ${INSTALL_DIR}/lc3sim) 
set(LC3SIM_C ${INSTALL_DIR}/lc3sim-c) 

set(DEFAULT_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../default_out) 

set(TYPE_OUT_STDOUT "stdout")
set(TYPE_OUT_FILE "file")

function(BuildObjFile a_OutObjFile a_InputFile a_OutBuildDir)
     message("a_InputFile = ${a_InputFile} a_OutBuildDir = ${a_OutBuildDir}")
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
        COMMENT "Compile ${a_InputFile} to ${obj_correct_file}"
    )

    set(cur_target_name ${a_OutBuildDir}_${out_file_name})
    message("cur_target_name = ${cur_target_name} a_OutBuildDir = ${a_OutBuildDir}")
    add_custom_target(${cur_target_name} ALL DEPENDS ${obj_correct_file})
endfunction()

function(BuildObjFiles a_OutObjFileList a_InputFileList a_OutBuildDir)
    set(out_list)
    message("BuildObjFiles a_InputFileList = ${a_InputFileList} a_OutBuildDir = ${a_OutBuildDir}")
    foreach(cur_file ${a_InputFileList})
        message("cur_file = ${cur_file}")
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

macro(AndRegressTests a_SimExe a_ObjFileList a_SourceFileList a_ExcludeSourceFileList a_AppendForNameTempFiles a_DefaultOutFile a_TypeOut)
    list(LENGTH a_ObjFileList obj_file_count)
    foreach(index RANGE 0 obj_file_count)
        list(GET a_ObjFileList index cur_obj_file)
        list(GET a_SourceFileList index cur_src_file)

        list(FIND a_ExcludeSourceFileList ${cur_src_file} find_src_file)
        if(NOT ${find_src_file} EQUAL -1)
            continue() # Cur source are exclude
        endif()

        AndRegressTest(${a_SimExe} ${cur_obj_file} ${cur_src_file} ${a_AppendForNameTempFiles} ${a_DefaultOutFile} ${a_TypeOut})
    endforeach()
endmacro()

function(MakeFileList a_OutFileList a_InputFileTemplateList)
    set(out_list)
    set(a_InputFileTemplateList1 ${a_InputFileTemplateList})
    message("a_InputFileTemplateList1 = ${a_InputFileTemplateList1}")

    foreach(cur_templete ${a_InputFileTemplateList})
        file(GLOB cur_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cur_templete}) 

        list(APPEND out_list ${cur_list})
        message("cur_list = ${cur_list}")
    endforeach()

    set(a_OutFileList out_list PARENT_SCOPE)
endfunction()
