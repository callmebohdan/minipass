#!/bin/bash

# Install CMake
sudo apt-get -y install cmake

# Install gcc
sudo apt-get -y install build-essential

# Install Qt6 prerequisites
sudo apt-get -y install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev libxcb-cursor0

# Install Qt6
sudo apt-get -y install qt6-base-dev qt6-base-dev-tools  qt6-tools-dev qt6-tools-dev-tools qt6ct qt6-multimedia-dev

# Install GTest
sudo apt-get -y install libgtest-dev

# Build and install static libraries
cd /usr/src/gtest && sudo cmake . && sudo make && sudo mv lib* /usr/lib/ && cd -

# Install XKB library
sudo apt install libxkbcommon-dev
