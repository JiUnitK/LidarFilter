cmake_minimum_required(VERSION 3.14)
project(LidarFilter)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)

file(GLOB SOURCES src/*.cpp)

add_executable(
  test_filter
  ${SOURCES}
  tests/test_filter.cpp
)

target_link_libraries(
  test_filter
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_filter)

