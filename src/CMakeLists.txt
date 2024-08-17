add_executable(MiniPass main.cpp minipass.cpp utils.cpp)

add_library(utils_lib utils.cpp)

add_library(minipass_lib minipass.cpp)

set_target_properties(MiniPass PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
