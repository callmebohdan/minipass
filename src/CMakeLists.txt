set(ASSET_FILES ../assets/minipass.rc)
set(CLI_HEADER_FILES utils.hpp minipass.hpp)
set(GUI_HEADER_FILES mainwindow.hpp utils.hpp minipass.hpp)
set(CLI_SOURCE_FILES mainCLI.cpp utils.cpp minipass.cpp)
set(GUI_SOURCE_FILES mainGUI.cpp mainwindow.cpp utils.cpp minipass.cpp)
set(UI_FILES mainwindow.ui)

add_library(utils_lib utils.cpp)
add_library(minipass_lib minipass.cpp)

add_executable(minipassCLI ${CLI_SOURCE_FILES} ${CLI_HEADER_FILES} ${ASSET_FILES})
qt_add_executable(minipassGUI ${GUI_SOURCE_FILES} ${GUI_HEADER_FILES} ${UI_FILES} ${ASSET_FILES})

target_link_libraries(minipassGUI PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

set_target_properties(minipassGUI PROPERTIES WIN64_EXECUTABLE ON LINK_FLAGS "-mwindows")
