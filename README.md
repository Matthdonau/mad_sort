# mad_sort_lib
## Intention
 This is a toy project for me to learn some things about sorting algorithms and NEON intrinsics.
 Only tested on an M1 Macbook Pro.

 ## Build instructions
    mkdir build && cd build
    cmake  -DCMAKE_BUILD_TYPE=Release ../
    
    # Build the library, tests and benchmarks
    cmake --build.

    # Run tests
    mad_sort_lib_tests/mad_sort_lib_tests

    # Run benchmarks
    mad_sort_lib_benchmarks/mad_sort_lib_benchmarks

