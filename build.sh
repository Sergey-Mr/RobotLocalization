#!/bin/bash

# Create build directory
mkdir -p build
cd build

# Configure
cmake ..

# Build
make -j$(nproc)

# Copy Python script
cp ../scripts/3dPlotting.py .