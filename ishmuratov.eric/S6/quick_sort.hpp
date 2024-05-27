#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <iterator>

namespace ishmuratov
{
  template < typename RandomIt >
  RandomIt partition(RandomIt begin, RandomIt end)
  {
    auto pivot = *(end - 1);
    auto i = begin;
    for (auto j = begin; j < end - 1; ++j)
    {
      if (*j < pivot)
      {
        std::iter_swap(i, j);
        ++i;
      }
    }
    std::iter_swap(i, end - 1);
    return i;
  }

  template < typename RandomIt >
  void quickSort(RandomIt begin, RandomIt end)
  {
    if (begin < end)
    {
      RandomIt pivot = partition(begin, end);
      quickSort(begin, pivot);
      quickSort(pivot + 1, end);
    }
  }
}

#endif
