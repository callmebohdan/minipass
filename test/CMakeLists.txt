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
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(TestMinipass test_minipass.cpp)
target_link_libraries(TestMinipass GTest::GTest minipass_lib)
add_test(NAME TestMiniPass COMMAND TestMinipass)

add_executable(TestUtils test_utils.cpp)
target_link_libraries(TestUtils GTest::GTest utils_lib)
add_test(NAME TestUtils COMMAND TestUtils)
