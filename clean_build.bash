#!/bin/bash

# Clean
echo "make clean"
cd build
make clean
#make clean_extra

# Remove build dir
echo "remove build/"
cd ..
rm -rf build/

