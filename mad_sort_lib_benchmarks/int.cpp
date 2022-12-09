#include "benchmark/benchmark.h"
#include "mad_sort.hpp"
#include <vector>
// Benchmarks for int type.

// std::sort
static void BM_STDSortInt(benchmark::State &state)
{
  std::vector<int> Test(state.range(0));
  std::generate(Test.begin(), Test.end(), std::rand);
  for (auto _ : state)
    STDSort(Test);
}
BENCHMARK(BM_STDSortInt)->Range(8, 8 << 13)->Unit(benchmark::kMicrosecond);

// C Quicksort
static void BM_QuickSortBaseLineInt(benchmark::State &state)
{
  std::vector<int> Test(state.range(0));
  std::generate(Test.begin(), Test.end(), std::rand);
  for (auto _ : state)
    QuickSortBaseLine(Test);
}
BENCHMARK(BM_QuickSortBaseLineInt)->Range(8, 8 << 13)->Unit(benchmark::kMicrosecond);

// Neon Quicksort
static void BM_MADSortInt(benchmark::State &state)
{
  std::vector<int> Test(state.range(0));
  std::generate(Test.begin(), Test.end(), std::rand);
  for (auto _ : state)
    MADSort(Test);
}
BENCHMARK(BM_MADSortInt)->Range(8, 8 << 13)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();