cmake_minimum_required(VERSION 3.10)

# Generate project
project(mad_sort)

# Some settings
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)

add_custom_target(mad_sort)
add_subdirectory(mad_sort_lib)
add_subdirectory(mad_sort_lib_benchmarks)
add_subdirectory(mad_sort_lib_tests)


add_dependencies(mad_sort mad_sort_lib mad_sort_lib_benchmarks mad_sort_lib_tests)
