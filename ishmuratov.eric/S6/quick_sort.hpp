#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <iterator>

namespace ishmuratov
{
  template < class RandomIt, class Compare >
  RandomIt do_partition(RandomIt begin, RandomIt end, Compare comp)
  {
    auto pivot = end - 1;
    auto i = begin;
    for (auto j = begin; j < end - 1; ++j)
    {
      if (comp(*j, *pivot))
      {
        std::iter_swap(i, j);
        ++i;
      }
    }
    std::iter_swap(i, end - 1);
    return i;
  }

  template < class RandomIt, class Compare >
  void quick_sort(RandomIt begin, RandomIt end, Compare comp)
  {
    if (begin < end)
    {
      RandomIt pivot = do_partition(begin, end, comp);
      quick_sort(begin, pivot, comp);
      quick_sort(pivot + 1, end, comp);
    }
  }
}

#endif
