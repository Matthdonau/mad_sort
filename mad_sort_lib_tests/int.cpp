#include "gtest/gtest.h"
#include "mad_sort.hpp"
#include <vector>
// Tests for int type.

// std::sort
TEST(STDSortInt, Basic)
{
  std::vector<int> Test{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> GT{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  STDSort(Test);

  for (int i = 0; i < 10; i++)
    ASSERT_EQ(GT[i], Test[i]);
}

TEST(STDSortInt, Random)
{
  int num = std::rand() % 100000;
  std::vector<int> Test(num);
  std::generate(Test.begin(), Test.end(), std::rand);
  STDSort(Test);

  for (size_t i = 1; i < Test.size(); i++)
    ASSERT_GE(Test[i], Test[i - 1]);
}

// C Quicksort
TEST(QuickSortBaseLineInt, Basic)
{
  std::vector<int> Test{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> GT{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  mad_sort::QuickSortBaseLine(Test);

  for (int i = 0; i < 10; i++)
    ASSERT_EQ(GT[i], Test[i]);
}

TEST(QuickSortBaseLineInt, Random)
{
  int num = std::rand() % 100000;
  std::vector<int> Test(num);
  std::generate(Test.begin(), Test.end(), std::rand);
  mad_sort::QuickSortBaseLine(Test);

  for (size_t i = 1; i < Test.size(); i++)
    ASSERT_GE(Test[i], Test[i - 1]);
}

// NEON
TEST(MADSortInt, Basic)
{
  std::vector<int> Test{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> GT{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  mad_sort::MADSort(Test);

  for (int i = 0; i < 10; i++)
    ASSERT_EQ(GT[i], Test[i]);
}

TEST(MADSortInt, Random)
{
  int num = std::rand() % 100000;
  std::vector<int> Test(num);
  std::generate(Test.begin(), Test.end(), std::rand);
  mad_sort::MADSort(Test);

  for (size_t i = 1; i < Test.size(); i++)
    ASSERT_GE(Test[i], Test[i - 1]);
}