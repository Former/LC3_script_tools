cmake_minimum_required(VERSION 3.10)
project(speed_test
    DESCRIPTION "speed_test project"
)

enable_testing()

include(../TestFunc.cmake)

set(OUT_DIR "build_speed")

set(src_files
    math/test1.c
    math/test2.c
    math/test3.c
    math/test4.c
    math/test_and.c
    math/test_div.c
    math/test_div1.c
    math/test_mul.c
    math/test_summ.c
    math/test_xor.c
    )

foreach (cur_file ${src_files})
    BuildAsmFile(out_asm_file ${cur_file} ${LC3_TARGET_LCC_NAME} ${OUT_DIR}16) 

    BuildObjFile(out_obj_file ${out_asm_file} ${cur_file} ${LC3AS} ${CORRECT_EXE} ${OUT_DIR}16) 
    
    AddSpeedTest(${LC3SIM_C16} ${out_obj_file} ${cur_file} "sim16" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    AddSpeedTest(${LC3SIM_CPP16} ${out_obj_file} ${cur_file} "sim_cpp16" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    AddSpeedTest(${LC3SIM} ${out_obj_file} ${cur_file} "def16" ${DEFAULT_OUT} ${TYPE_OUT_FILE})

    BuildAsmFile(out_asm_file ${cur_file} ${LC3_32_TARGET_LCC_NAME} ${OUT_DIR}32) 

    BuildObjFile(out_obj_file ${out_asm_file} ${cur_file} ${LC3AS32} ${CORRECT32_EXE} ${OUT_DIR}32) 
    
    AddSpeedTest(${LC3SIM_C32} ${out_obj_file} ${cur_file} "sim32" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    AddSpeedTest(${LC3SIM_CPP32} ${out_obj_file} ${cur_file} "sim_cpp32" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})

    BuildObjFile(out_obj_file ${out_asm_file} ${cur_file} ${LC3AS32W} ${CORRECT32W_EXE} ${OUT_DIR}32W) 
    AddSpeedTest(${LC3SIM_CPP32W} ${out_obj_file} ${cur_file} "sim_cpp32w" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})

    BuildObjFile(out_obj_file ${out_asm_file} ${cur_file} ${LC3AS64W} ${CORRECT64W_EXE} ${OUT_DIR}64W) 
    AddSpeedTest(${LC3SIM_CPP64W} ${out_obj_file} ${cur_file} "sim_cpp64w" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})

    BuildNative(out_native_file ${cur_file})
    AddSpeedTest("null" ${CMAKE_CURRENT_BINARY_DIR}/${out_native_file} ${cur_file} "nativeO0" ${DEFAULT_OUT} ${TYPE_OUT_NATIVE})
endforeach()

