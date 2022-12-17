cmake_minimum_required(VERSION 3.10)

# Generate project
project(mad_sort_lib)

# Some settings
set (CMAKE_CXX_STANDARD 11)
set (CXX_STANDARD_REQUIRED ON)

# Source files
set(MAD_SORT_SOURCES
    "mad_sort.cpp"
)
set(MAD_SORT_HEADERS
    "mad_sort.hpp"
)

# Compile options
# -g to have symbols for performance profiling
add_compile_options(-Wall -Wextra -Wpedantic -O2 -g3)

# Generate a library as well
add_library(mad_sort_lib SHARED ${MAD_SORT_SOURCES} ${MAD_SORT_HEADERS})
