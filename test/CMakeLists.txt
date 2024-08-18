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

add_executable(TestMinipass test_minipass.cpp)
add_executable(TestUtils test_utils.cpp)

target_link_libraries(TestMinipass PRIVATE gtest gtest_main minipass_lib)
target_link_libraries(TestUtils PRIVATE gtest gtest_main utils_lib)
