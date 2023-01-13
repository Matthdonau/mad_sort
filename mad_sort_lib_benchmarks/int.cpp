#include "benchmark/benchmark.h"
#include "mad_sort.hpp"
#include <vector>
// Benchmarks for int type.

// std::sort
static void BM_STDSortInt(benchmark::State &state)
{
  std::vector<int> Test(state.range(0));
  for (auto _ : state)
  {
    std::generate(Test.begin(), Test.end(), std::rand);
    STDSort(Test);
  }
}
BENCHMARK(BM_STDSortInt)->Range(8, 8 << 13)->Unit(benchmark::kMicrosecond);

// C Quicksort
static void BM_QuickSortBaseLineInt(benchmark::State &state)
{
  std::vector<int> Test(state.range(0));
  for (auto _ : state)
  {
    std::generate(Test.begin(), Test.end(), std::rand);
    mad_sort::QuickSortBaseLine(Test);
  }
}
BENCHMARK(BM_QuickSortBaseLineInt)->Range(8, 8 << 13)->Unit(benchmark::kMicrosecond);

// Neon Quicksort
static void BM_MADSortInt(benchmark::State &state)
{
  std::vector<int> Test(state.range(0));
  for (auto _ : state)
  {
    std::generate(Test.begin(), Test.end(), std::rand);
    mad_sort::MADSort(Test);
  }
}
BENCHMARK(BM_MADSortInt)->Range(8, 8 << 13)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();