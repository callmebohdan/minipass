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

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Boost REQUIRED COMPONENTS program_options filesystem system)

set(HEADER_FILES src/minipass.hpp)
set(SOURCE_FILES src/main.cpp src/minipass.cpp)
set(UI_FILES resources/minipass.ui)
set(QRC_FILE resources/minipass.qrc)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})
qt_add_resources(GENERATED_RESOURCES ${QRC_FILE})  # Properly process QRC file

if(WIN32)
    set(ASSET_FILES resources/minipass.rc)
    qt_add_executable(minipass WIN32 ${SOURCE_FILES} ${HEADER_FILES} ${GENERATED_RESOURCES} ${ASSET_FILES})
else()
    qt_add_executable(minipass ${SOURCE_FILES} ${HEADER_FILES} ${GENERATED_RESOURCES})
endif()

target_link_libraries(minipass PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Boost::program_options Boost::filesystem Boost::system)

option(ENABLE_TESTS "Enable test suite" OFF)
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()