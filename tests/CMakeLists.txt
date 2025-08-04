cmake_minimum_required(VERSION 3.15)
project(ShapeRendererTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ShapeRendererTests ShapeRendererTests.cpp)
target_link_libraries(ShapeRendererTests
    PRIVATE geometry
            GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ShapeRendererTests)
