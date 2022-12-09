#include <iostream>
#include <array>
#include "mad_sort.hpp"

int main(void)
{
    // NEON Support on this platform?
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
    std::cout << "NEON Supported"
              << "\n";
#endif

    std::vector<int32_t> test{9, 8, 7, 6, 5, 4, 3, 2, 1};

    // std::sort
    STDSort(test);
    for (auto const &el : test)
        std::cout << el << "\t";

    std::cout << "\n";

    // mad_sort
    MADSort(test);
    for (auto const &el : test)
        std::cout << el << "\t";

    QuickSortBaseLine(test);
    return 1;
}