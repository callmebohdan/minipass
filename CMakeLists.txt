cmake_minimum_required (VERSION 3.22)

project (minipass LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

add_subdirectory(src)

option(ENABLE_TESTS "Enable test suite" OFF)
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()