#!/bin/bash
set -e

# Set QT_QPA_PLATFORM to xcb for running on xcb
export QT_QPA_PLATFORM=xcb

# Save the current directory
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

# Navigate up one level from the scripts directory
cd "$SCRIPT_DIR/.."

# Store the current directory (project root) in PROJECT_DIR
PROJECT_DIR=$(pwd)

BUILD_DIR="$PROJECT_DIR/build"
BIN_DIR="$PROJECT_DIR/bin"
QT_PATH="/usr/lib/x86_64-linux-gnu/cmake/Qt6"
QT_LIB_PATH="/usr/lib/x86_64-linux-gnu"

# Clean previous build if exists
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

if [ -d "$BIN_DIR" ]; then
    echo "Cleaning previous build bin/..."
    rm -rf "$BIN_DIR"
fi

# Create build directory
echo "Creating build directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"


# Configure the project with CMake
echo "Running CMake configuration..."
cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH="$QT_PATH" "$PROJECT_DIR"

# Build the project
echo "Building the project..."
make

# Copy the executable and necessary libraries into the bin directory
if [ -f "$BUILD_DIR/src/minipassGUI" ]; then
    mkdir -p "$BIN_DIR"
    echo "Copying the application into the bin/ directory..."
    cp "$BUILD_DIR/src/minipassCLI" "$BIN_DIR"
    cp "$BUILD_DIR/src/minipassGUI" "$BIN_DIR"
    cp "$QT_LIB_PATH/libQt6Core.so.6" "$BIN_DIR"
    cp "$QT_LIB_PATH/libQt6Gui.so.6" "$BIN_DIR"
    cp "$QT_LIB_PATH/libQt6Widgets.so.6" "$BIN_DIR"
else
    echo "Error: minipassGUI was not created."
    exit 1
fi

if [ -f "$BUILD_DIR/test/TestMinipass" ]; then
    echo "Copying the tests into the bin/ directory..."
    cp "$BUILD_DIR/test/TestMinipass" "$BIN_DIR"
else
    echo "Error: tests were not created."
    exit 1
fi

# Run the executable if it was created
if [ -f "$BIN_DIR/minipassGUI" ]; then
    echo "Running the application..."
    "$BIN_DIR/minipassGUI"
else
    echo "Error: minipassGUI was not created."
    exit 1
fi

