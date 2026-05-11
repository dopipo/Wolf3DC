#!/bin/bash
# Build script for Wolf3DC compiler

echo "Building W3D Compiler..."
mkdir -p build
cd build
cmake ..
make
cd ..

echo ""
echo "Testing compilation..."
echo ""

# Run the compiler with test file
./build/w3d_compiler test/example.c test/example_out.cpp

echo ""
echo "Checking log file:"
echo "-------------------"
if [ -f w3d_compiler.log ]; then
    cat w3d_compiler.log
else
    echo "ERROR: Log file not created!"
fi
