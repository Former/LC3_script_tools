cmake_minimum_required(VERSION 3.10)
project(lcc-1.3
	DESCRIPTION "lcc-1.3 project"
)

set(EXTRA_COMPILE_OPTIONS -O2)

add_subdirectory(cpp)
add_subdirectory(etc)
add_subdirectory(lburg)
add_subdirectory(lc3pp)
add_subdirectory(lib)
add_subdirectory(src)
