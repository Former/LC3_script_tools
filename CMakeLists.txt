cmake_minimum_required(VERSION 3.10)
project(lc3
	DESCRIPTION "lc3 project"
)

add_subdirectory(lc3tools)
add_subdirectory(lcc-1.3)
add_subdirectory(lc3sim-c)

enable_testing()
add_subdirectory(test)
