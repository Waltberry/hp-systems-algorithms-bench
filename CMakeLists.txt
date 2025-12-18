cmake_minimum_required(VERSION 3.16)
project(hp_systems_algorithms_bench LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Build tests" ON)

add_executable(bench
  src/main.cpp
  src/bench.cpp
)
target_include_directories(bench PRIVATE include)
target_compile_options(bench PRIVATE -O3)

if(ENABLE_TESTS)
  enable_testing()
  add_executable(test_stats tests/test_stats.cpp src/bench.cpp)
  target_include_directories(test_stats PRIVATE include)
  add_test(NAME test_stats COMMAND test_stats)
endif()
