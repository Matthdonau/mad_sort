cmake_minimum_required(VERSION 3.10)

# Generate project
project(mad_sort_lib_benchmarks)

# Some settings
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)

# Compile options
add_compile_options(-Wall -Wextra -pedantic -Werror -g3)

# Generate executable
add_executable(mad_sort_lib_benchmarks)
set(MAD_SORT_BENCHMARKS_SOURCES
    "int.cpp"
)
target_sources(mad_sort_lib_benchmarks PRIVATE ${MAD_SORT_BENCHMARKS_SOURCES} )

# mad_sort
add_dependencies(mad_sort_lib_benchmarks mad_sort_lib)

# Google benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
  google_benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(google_benchmark)
include_directories(mad_sort_lib_benchmarks ${google_benchmark_SOURCE_DIR}/include/ ${CMAKE_SOURCE_DIR}/mad_sort_lib/)
target_link_libraries(mad_sort_lib_benchmarks benchmark::benchmark mad_sort_lib)