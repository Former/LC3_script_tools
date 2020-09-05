set(INSTALL_DIR "${CMAKE_BINARY_DIR}/bin")

set(LCC ${INSTALL_DIR}/lcc) 
set(LC3AS ${INSTALL_DIR}/lc3as) 
set(LC3AS32 ${INSTALL_DIR}/lc3as32) 
set(LC3AS32W ${INSTALL_DIR}/lc3as32w) 
set(LC3AS64W ${INSTALL_DIR}/lc3as64w) 

set(LC3SIM ${INSTALL_DIR}/lc3sim) 
set(LC3SIM_C16 ${INSTALL_DIR}/lc3sim-c16) 
set(LC3SIM_C32 ${INSTALL_DIR}/lc3sim-c32) 

set(LC3SIM_CPP16 ${INSTALL_DIR}/lc3sim_cpp16) 
set(LC3SIM_CPP32 ${INSTALL_DIR}/lc3sim_cpp32) 
set(LC3SIM_CPP32W ${INSTALL_DIR}/lc3sim_cpp32w) 
set(LC3SIM_CPP64W ${INSTALL_DIR}/lc3sim_cpp64w) 

set(CORRECT_EXE ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj_file)
set(CORRECT32_EXE ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj32_file)
set(CORRECT32W_EXE ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj32w_file)
set(CORRECT64W_EXE ${CMAKE_CURRENT_SOURCE_DIR}/../correct_obj64w_file)

set(LC3_TARGET_LCC_NAME "lc3") 
set(LC3_32_TARGET_LCC_NAME "lc3_32bit") 

set(DEFAULT_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../default_out) 

set(TYPE_OUT_STDOUT "stdout")
set(TYPE_OUT_NATIVE "native")
set(TYPE_OUT_FILE "file")

function(BuildAsmFile a_OutAsmFile a_InputFile a_TargetName a_OutBuildDir)
    set(raw_template_out_file
        ${CMAKE_CURRENT_BINARY_DIR}/${a_OutBuildDir}/${a_InputFile}
        )

    get_filename_component(out_file_dir ${raw_template_out_file} DIRECTORY)
    get_filename_component(out_file_name ${raw_template_out_file} NAME)
    get_filename_component(out_file_name_we ${raw_template_out_file} NAME_WE)

    set(template_out_file 
        ${out_file_dir}/${out_file_name_we}
        )
    set(${a_OutAsmFile} ${template_out_file}.asm PARENT_SCOPE)

    add_custom_command(
        OUTPUT ${template_out_file}.asm
        COMMAND mkdir -p ${out_file_dir}
        COMMAND ${LCC} -target=${a_TargetName} -L ${CMAKE_CURRENT_SOURCE_DIR}/${a_InputFile} -o ${template_out_file}
        DEPENDS lcc rcc cpp ${CMAKE_CURRENT_SOURCE_DIR}/${a_InputFile}
        COMMENT "Compile ${a_OutBuildDir}/${a_InputFile}"
    )
endfunction()

function(BuildObjFile a_OutObjFile a_InputAsmFile a_InputFile a_AsmExe a_CorrectExe a_OutBuildDir)
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

    if (NOT ${a_InputAsmFile} STREQUAL ${template_out_file}.asm)
        add_custom_command(
            OUTPUT ${template_out_file}.asm
            COMMAND mkdir -p ${out_file_dir}
            COMMAND cp ${a_InputAsmFile} ${template_out_file}.asm
            #WORKING_DIRECTORY ${out_file_dir}
            DEPENDS ${a_InputAsmFile}
            COMMENT "Copy_asm ${a_InputAsmFile} to ${template_out_file}.asm"
        )
    endif()

    add_custom_command(
        OUTPUT ${obj_file}
        COMMAND ${a_AsmExe} ${template_out_file}.asm
        WORKING_DIRECTORY ${out_file_dir}
        DEPENDS ${a_AsmExe} ${template_out_file}.asm
        COMMENT "Asm ${obj_file}"
    )

    add_custom_command(
        OUTPUT ${obj_correct_file}
        COMMAND ${a_CorrectExe} ${obj_file} ${obj_correct_file}
        WORKING_DIRECTORY ${out_file_dir}
        DEPENDS ${obj_file}
        COMMENT "Correct to ${obj_correct_file}"
    )

    BuildNameFromPath(input_name ${a_InputAsmFile})
    set(cur_target_name ${a_OutBuildDir}_${input_name})
    add_custom_target(${cur_target_name} ALL DEPENDS ${obj_correct_file})
endfunction()

function(BuildNameFromPath a_OutName a_Path)
    string(REPLACE "/" "_" out_name ${a_Path})

    set(${a_OutName} ${out_name} PARENT_SCOPE)
endfunction()

function(BuildObjFiles a_OutObjFileList a_InputFileList a_TargetName a_AsmExe a_CorrectExe a_OutBuildDir)
    set(out_list)
    foreach(cur_file ${a_InputFileList})
        BuildObjFile(out_file ${cur_file} ${a_TargetName} ${a_AsmExe} ${a_CorrectExe} ${a_OutBuildDir}) 

        list(APPEND out_list ${out_file})
    endforeach()

    set(${a_OutObjFileList} ${out_list} PARENT_SCOPE)
endfunction()

function(AddTest a_TestType a_SimExe a_ObjFile a_SourceFile a_AppendForNameTempFiles a_DefaultOutFile a_TypeOut)
    add_test(NAME ${a_TestType}_${a_AppendForNameTempFiles}__${a_SourceFile}
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

function(AddRegressTest a_SimExe a_ObjFile a_SourceFile a_AppendForNameTempFiles a_DefaultOutFile a_TypeOut)
    AddTest(regress_test ${a_SimExe} ${a_ObjFile} ${a_SourceFile} ${a_AppendForNameTempFiles} ${a_DefaultOutFile} ${a_TypeOut})
endfunction()

function(AddSpeedTest a_SimExe a_ObjFile a_SourceFile a_AppendForNameTempFiles a_DefaultOutFile a_TypeOut)
    AddTest(speed_test ${a_SimExe} ${a_ObjFile} ${a_SourceFile} ${a_AppendForNameTempFiles} ${a_DefaultOutFile} ${a_TypeOut})
endfunction()
