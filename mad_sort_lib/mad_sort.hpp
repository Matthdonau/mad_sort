#include <vector>

#ifndef MAD_SORT_HPP
#define MAD_SORT_HPP

#define EXPORT __attribute__((visibility("default")))
#define IMPORT

// std::sort for a baseline
template <typename T>
EXPORT void STDSort(std::vector<T> &in)
{
    return std::sort(in.begin(), in.end());
}

namespace mad_sort
{
    // Standard quick sort in c++.
    template <typename T>
    EXPORT void QuickSortBaseLine(std::vector<T> &in);

#if defined(__ARM_NEON) || defined(__ARM_NEON__)

    // Declarations for all sane int types.
    EXPORT void MADSort(std::vector<int32_t> &in);
    EXPORT void MADSort(std::vector<int16_t> &in);

#else // No NEON Support

    // In case no of no NEON support fallback to std::sort
    template <typename T>
    EXPORT void MADSort(std::vector<T> &in)
    {
        return std::sort(in.begin(), in.end());
    }

#endif
}

#endif //#ifndef MAD_SORT_HPP