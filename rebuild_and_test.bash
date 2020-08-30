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
time ctest -R regress -j $1

# Run unit test
ctest -R unittest -j

# Run speed test
ctest -R speed_test 
