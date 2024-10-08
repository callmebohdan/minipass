﻿find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(ASSET_FILES ../assets/icon/minipass.rc)
set(HEADER_FILES utils.hpp minipass.hpp)
set(SOURCE_FILES main.cpp utils.cpp minipass.cpp)
set(UI_FILES minipass.ui)

# add_library(utils_lib utils.cpp)
# add_library(minipass_lib minipass.cpp)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

if (WIN32)
    qt_add_executable(minipass WIN32 ${SOURCE_FILES} ${HEADER_FILES} ${UI_HEADERS} ${ASSET_FILES})
else()
    qt_add_executable(minipass ${SOURCE_FILES} ${HEADER_FILES} ${UI_HEADERS} ${ASSET_FILES})
endif()

target_link_libraries(minipass PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# target_link_libraries(utils_lib Qt6::Core)
# target_link_libraries(minipass_lib Qt6::Core Qt6::Gui Qt6::Multimedia Qt6::Widgets Qt6::MultimediaWidgets)
