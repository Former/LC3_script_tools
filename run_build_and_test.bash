#!/bin/bash

# Clean
./clean_build.bash

# Build
echo "Run cmake"
mkdir build
cd build
cmake .. 
make -j

# Run test
echo "Run ctest"
ctest -j

