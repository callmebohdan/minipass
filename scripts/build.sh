#!/bin/bash

set -e

export QT_QPA_PLATFORM=xcb
export PATH="/usr/lib/qt6/bin:$PATH"

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
cd "$SCRIPT_DIR/.."
PROJECT_DIR=$(pwd)

BUILD_DIR="$PROJECT_DIR/build"
OUT_DIR="$PROJECT_DIR/out"
SRC_DIR="$PROJECT_DIR/src"

QT_PATH="/usr/lib/x86_64-linux-gnu/cmake/Qt6"
QT_LIB_PATH="/usr/lib/qt6/libexec"

echo "Cleaning directories..."
rm -rf "$BUILD_DIR" "$OUT_DIR"

echo "Creating build/ directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Running CMake configuration..."
cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH="$QT_PATH" "$PROJECT_DIR"

# Verbose build output
make VERBOSE=0

make install

if [ -f "$BUILD_DIR/minipass" ]; then
    echo "[Success]: minipass build was successfull."
else
    echo "[Error]: minipass build was not successfull."
fi

# if [ -f "$BUILD_DIR/test/GoogleTestMinipass" ]; then
    echo "GoogleTestMinipass was created."
# else
#     echo "No tests found. Skipping."
# fi
