set(ASSET_FILES ../assets/icon/minipass.rc)
set(HEADER_FILES utils.hpp minipass.hpp)
set(SOURCE_FILES main.cpp utils.cpp minipass.cpp)
set(UI_FILES minipass.ui)

add_library(utils_lib utils.cpp)
add_library(minipass_lib minipass.cpp)

qt_add_executable(minipass ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES} ${ASSET_FILES})

target_link_libraries(minipass PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

if (WIN32)
    set_target_properties(minipass PROPERTIES WIN64_EXECUTABLE ON LINK_FLAGS "-mwindows")
endif()
