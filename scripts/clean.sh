#!/bin/bash

set -e

PROJECT_DIR=$(pwd)

BUILD_DIR="$PROJECT_DIR/build"
BIN_DIR="$PROJECT_DIR/bin"

# Clean previous build if exists
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

# Clean previous build bin directory if exists
if [ -d "$BIN_DIR" ]; then
    echo "Cleaning previous build bin/..."
    rm -rf "$BIN_DIR"
fi
