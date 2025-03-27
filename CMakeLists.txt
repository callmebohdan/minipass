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

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Concurrent)
find_package(Boost REQUIRED COMPONENTS program_options filesystem system)

set(HEADER_FILES src/minipass.hpp)
set(SOURCE_FILES src/main.cpp src/minipass.cpp)
set(UI_FILES resources/minipass.ui)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

if(WIN32)
    set(ASSET_FILES resources/minipass.rc)
    qt_add_executable(minipass WIN32 ${SOURCE_FILES} ${HEADER_FILES} ${ASSET_FILES})
else()
    qt_add_executable(minipass ${SOURCE_FILES} ${HEADER_FILES})
    install(TARGETS minipass DESTINATION /usr/bin)
endif()

target_link_libraries(minipass PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Concurrent Boost::program_options Boost::filesystem Boost::system)

option(ENABLE_TESTS "Enable test suite" ON)
if (ENABLE_TESTS)
    enable_testing()

    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    endif()

    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    FetchContent_MakeAvailable(googletest)

    add_library(minipass_lib src/minipass.cpp)
    
    add_executable(GoogleTestMinipass src/test/googletest_minipass.cpp)

    target_link_libraries(minipass_lib Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Concurrent Boost::program_options Boost::filesystem Boost::system)
    target_link_libraries(GoogleTestMinipass PRIVATE gtest gtest_main minipass_lib)

endif()