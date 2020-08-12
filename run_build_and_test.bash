#!/bin/bash

# Clean
time ./clean_build.bash

# Build
echo "Run cmake"
mkdir build
cd build
time cmake .. 
time make -j $1

# Run test
echo "Run ctest"
time ctest -j $1




