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
    )

foreach (cur_file ${src_files})
    BuildObjFile(out_obj_file ${cur_file} ${LC3_TARGET_LCC_NAME} ${LC3AS} ${CORRECT_EXE} ${OUT_DIR}16) 
    
    AddSpeedTest(${LC3SIM_C16} ${out_obj_file} ${cur_file} "sim16" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    AddSpeedTest(${LC3SIM_CPP16} ${out_obj_file} ${cur_file} "sim_cpp16" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    AddSpeedTest(${LC3SIM} ${out_obj_file} ${cur_file} "def16" ${DEFAULT_OUT} ${TYPE_OUT_FILE})

    BuildObjFile(out_obj_file ${cur_file} ${LC3_32_TARGET_LCC_NAME} ${LC3AS32} ${CORRECT32_EXE} ${OUT_DIR}32) 
    
    AddSpeedTest(${LC3SIM_C32} ${out_obj_file} ${cur_file} "sim32" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
    AddSpeedTest(${LC3SIM_CPP32} ${out_obj_file} ${cur_file} "sim_cpp32" ${DEFAULT_OUT} ${TYPE_OUT_STDOUT})
endforeach()
