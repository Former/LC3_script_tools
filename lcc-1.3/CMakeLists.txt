cmake_minimum_required(VERSION 3.10)
project(lcc-1.3
    DESCRIPTION "lcc-1.3 project"
)

set(OPTIMIZE_COMPILE_OPTION -O0)
set(EXTRA_COMPILE_OPTIONS ${OPTIMIZE_COMPILE_OPTION})

add_subdirectory(cpp)
add_subdirectory(etc)
add_subdirectory(lburg)
add_subdirectory(lc3pp)
add_subdirectory(lib)
add_subdirectory(src)
