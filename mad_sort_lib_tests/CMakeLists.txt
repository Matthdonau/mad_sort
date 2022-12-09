cmake_minimum_required(VERSION 3.10)

# Generate project
project(mad_sort_lib_tests)

# Some settings
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)

# Compile options
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Generate executable
add_executable(mad_sort_lib_tests)
set(MAD_SORT_BENCHMARKS_SOURCES
    "int.cpp"
)
target_sources(mad_sort_lib_tests PRIVATE ${MAD_SORT_BENCHMARKS_SOURCES} )

# mad_sort
add_dependencies(mad_sort_lib_tests mad_sort_lib)

# Google benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(gtest)
message(${CMAKE_SOURCE_DIR}) 
include_directories(mad_sort_lib_tests ${gtest_SOURCE_DIR}/include/ ${CMAKE_SOURCE_DIR}/mad_sort_lib/)
target_link_libraries(mad_sort_lib_tests gtest_main mad_sort_lib)