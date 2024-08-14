cmake_minimum_required (VERSION 3.8)

project ("minipass")

add_executable(minipass
    src/main.cpp
    src/minipass.cpp
    src/utils.cpp
)

target_include_directories(minipass PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
)
