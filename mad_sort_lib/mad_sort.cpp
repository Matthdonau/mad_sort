#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <limits>
#include "mad_sort.hpp"

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#endif
namespace mad_sort
{
    /*---------------------------------------------------------------------------*/
    /*------------------------------------ C ------------------------------------*/
    /*---------------------------------------------------------------------------*/
    template <typename T>
    void Swap(T *a, T *b)
    {
        T const t = *a;
        *a = *b;
        *b = t;
    }

    template <typename T>
    size_t Partition(std::vector<T> &in, size_t low, size_t high)
    {
        // Determine pivot element val.
        T pivot = in[low];

        // Determine number of elements left to pivot (+1).
        size_t count = 0;
        for (size_t i = low + 1; i <= high; i++)
            if (in[i] <= pivot)
                count++;

        size_t pivot_idx = low + count;
        Swap(&in[pivot_idx], &in[low]);

        // Put every element > pivot right to the pivot index and
        // every element <= pivot left to the pivot index.
        size_t i = low, j = high;
        while (i < pivot_idx && j > pivot_idx)
        {

            while (in[i] <= pivot)
                i++;

            while (in[j] > pivot)
                j--;

            if (i < pivot_idx && j > pivot_idx)
                Swap(&in[i++], &in[j--]);
        }

        // Return the pivot index.
        return pivot_idx;
    }

    template <typename T>
    void QuickSortBaseLineAlgo(std::vector<T> &in, size_t low, size_t high)
    {
        // Exit condition
        if (low >= high)
            return;

        size_t pivot = Partition(in, low, high);

        // Call QSort recursive with both sides of pivot.
        if (pivot > low)
            QuickSortBaseLineAlgo(in, low, pivot - 1);
        if (pivot < high)
            QuickSortBaseLineAlgo(in, pivot + 1, high);
    }

    template <typename T>
    void QuickSortBaseLine(std::vector<T> &in)
    {
        QuickSortBaseLineAlgo(in, 0, in.size() - 1);
    }
    template void QuickSortBaseLine<int>(std::vector<int> &in);

/*---------------------------------------------------------------------------*/
/*----------------------------------- NEON ----------------------------------*/
/*---------------------------------------------------------------------------*/
#if defined(__ARM_NEON) || defined(__ARM_NEON__)

    // Quick-Sort
    size_t inline MADQuickSortPartition(std::vector<int32_t> &in, size_t low, size_t high)
    {
        // Partition
        int32_t pivot = in[low];
        size_t num_left = 0;
        size_t curr = low + 1;
        size_t counter = 0;

        // Constants for bit manipulation stuff
        int32x4_t sum = vmovq_n_s32(0);
        int32x4_t const one = vmovq_n_s32(1);
        size_t max_sum = std::numeric_limits<int32_t>::max() / 4;
        if (high >= 4)
        {
            for (; curr <= high - 4; curr += 4)
            {
                // Since we cann only accumulate to int_32 max value we sometimes have to accumulate sequentially,
                // add it to the overall num and zero out the sum.
                if (counter >= max_sum)
                {
                    int32_t const num = vaddvq_s32(sum);
                    num_left += num;
                    sum = vmovq_n_s32(0);
                    counter = 0;
                }

                // Find number of elements smaller than current or euqal to current pivot.
                int32x4_t const input = vld1q_s32(&in[curr]);
                int32x4_t const to_compare = vmovq_n_s32(pivot);
                int32x4_t const res = vcleq_s32(input, to_compare);
                int32x4_t const summand = vandq_s32(res, one);
                sum = vaddq_s32(sum, summand);
                counter++;
            }
            if (counter > 0)
            {
                int32_t const num = vaddvq_s32(sum);
                num_left += num;
            }
        }
        // Remainder
        for (size_t i = curr; i <= high; i++)
        {
            if (in[i] <= pivot)
                num_left++;
        }

        // Swap current low to pivot idx.
        size_t pivot_idx = low + num_left;
        Swap(&in[pivot_idx], &in[low]);

        // Put every element > pivot right to the pivot index and
        // every element <= pivot left to the pivot index.
        size_t i = low, j = high;
        size_t last_i = low;
        size_t last_j = high;
        while (i < pivot_idx && j > pivot_idx)
        {

            // Find first element left to pivot_idx which is greater than pivot.
            int32_t num = 0;
            if (i >= last_i + (-num))
            {
                for (size_t indx = i; indx < pivot_idx - 4; indx += 4) // pivot_idx -4 might be a problem due to size_t
                {
                    i = last_i = indx;
                    int32x4_t const input = vld1q_s32(&in[indx]);
                    int32x4_t const to_compare = vmovq_n_s32(pivot);
                    int32x4_t const res = vcleq_s32(input, to_compare);
                    num = vaddvq_s32(res);

                    if (num != -4)
                        break;
                }
            }
            // Either there is less than 4 elements left to pivot_idx or we did find a 4-pack
            // of which at least one isnt greater than pivot. Find which one of them and proceed.
            while (in[i] <= pivot)
                i++;

            // Find first element which is right to pivot_idx and smaller than pivot.
            if (pivot_idx >= 3 && j >= 3 && j + 4 <= last_j)
            {
                for (size_t indx = j - 3; indx > pivot_idx; indx -= 4)
                {
                    j = last_j = j;
                    int32x4_t const input = vld1q_s32(&in[indx]);
                    int32x4_t const to_compare = vmovq_n_s32(pivot);
                    int32x4_t const res = vcgtq_s32(input, to_compare);
                    int32_t const num = vaddvq_s32(res);

                    if (num != -4)
                        break;
                }
            }
            // Either there is less than 4 elements left to pivot_idx or we did find a 4-pack
            // of which at least one isnt smaller than pivot. Find which one of them and proceed.
            while (in[j] > pivot)
                j--;

            if (i < pivot_idx && j > pivot_idx)
                Swap(&in[i++], &in[j--]);
        }

        // Return the pivot index.
        return pivot_idx;
    }

    void inline MADQuickSortBaseLineAlgo(std::vector<int32_t> &in, size_t low, size_t high)
    {
        // Exit condition
        if (low >= high)
            return;

        size_t pivot = MADQuickSortPartition(in, low, high);

        // Call QSort recursive with both sides of pivot.
        if (pivot > low)
            MADQuickSortBaseLineAlgo(in, low, pivot - 1);
        if (pivot < high)
            MADQuickSortBaseLineAlgo(in, pivot + 1, high);
    }

    void MADSort(std::vector<int32_t> &in)
    {
        // We do have 128 bytes in each NEON register which means for int32_t
        // we are able to process 4 elements of "in" at once.
        // Therefore only use NEON instructions if "in" holds more than 4 elements.
        if (in.size() >= 4)
        {
            MADQuickSortBaseLineAlgo(in, 0, in.size() - 1);
        }
        else
            STDSort(in);
    }

#endif
}
