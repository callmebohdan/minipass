#!/bin/bash

# Retrieve new lists of packages
sudo apt-get update

# Perform an upgrade
sudo apt-get -y upgrade

# Install CMake
sudo apt-get -y install cmake

# Install GCC
sudo apt-get -y install build-essential

# Install Qt6
sudo apt-get -y install qt6-base-dev qt6-base-dev-tools qt6-tools-dev \ 
    qt6-tools-dev-tools qt6ct qt6-multimedia-dev libgl1-mesa-dev \
    libglu1-mesa-dev freeglut3-dev mesa-common-dev libxcb-cursor0


# Install XKB library
sudo apt-get -y install libxkbcommon-dev

# Install and build GTest static libraries
sudo apt-get -y install libgtest-dev
cd /usr/src/gtest
cmake .
make
mv lib/libgtest* /usr/lib/
cd -
