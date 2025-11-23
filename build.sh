#!/bin/bash
# Build script for Chess Game on Linux/macOS

echo "Building Chess Game..."
echo ""

# Create build directory if it doesn't exist
if [ ! -d build ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "CMake configuration failed. Please ensure Qt 5 is installed."
    exit 1
fi

# Build the project
echo ""
echo "Building project..."
cmake --build . --config Release

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Build successful!"
echo ""
echo "To run the game, execute: ./ChessGame"
