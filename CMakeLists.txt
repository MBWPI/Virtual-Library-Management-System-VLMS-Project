cmake_minimum_required(VERSION 3.10)
project(UserLibraryTest)

set(CMAKE_CXX_STANDARD 11)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    UserLibraryTest
    testing.cpp
    functions.cpp
)

target_link_libraries(
    UserLibraryTest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UserLibraryTest)
