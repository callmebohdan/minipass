#!/bin/bash

set -e

export QT_QPA_PLATFORM=xcb
export PATH="/usr/lib/qt6/bin:$PATH"

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
cd "$SCRIPT_DIR/.."
PROJECT_DIR=$(pwd)

BIN_DIR="$PROJECT_DIR/bin"
BUILD_DIR="$PROJECT_DIR/build"
OUT_DIR="$PROJECT_DIR/out"
SRC_DIR="$PROJECT_DIR/src"

QT_PATH="/usr/lib/x86_64-linux-gnu/cmake/Qt6"
QT_BIN_PATH="/usr/lib/qt6/bin"
QT_LIB_PATH="/usr/lib/qt6/libexec"

echo "Cleaning directories..."
rm -rf "$BIN_DIR" "$BUILD_DIR" "$OUT_DIR"

echo "Creating build/ directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Running CMake configuration..."
cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH="$QT_PATH" "$PROJECT_DIR"

echo "Generating ui_minipass.h..."
"$QT_LIB_PATH/uic" "$SRC_DIR/minipass.ui" -o "$SRC_DIR/ui_minipass.h"

# Verbose build output
make VERBOSE=1
if [ -f "$BUILD_DIR/src/minipass" ]; then
    mkdir -p "$BIN_DIR"
    echo "Copying the application into bin/..."
    cp "$BUILD_DIR/src/minipass" "$BIN_DIR"
else
    echo "Error: minipass build was not successfull."
fi

# if [ -f "$BUILD_DIR/test/TestMinipass" ]; then
#     echo "Copying tests into bin/..."
#     cp "$BUILD_DIR/test/TestMinipass" "$BIN_DIR"
# else
#     echo "No tests found. Skipping."
# fi
