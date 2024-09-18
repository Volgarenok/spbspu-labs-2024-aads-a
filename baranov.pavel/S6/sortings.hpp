#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include <iterator>
#include <iostream>

namespace baranov
{
  template< typename BiDirIterator, typename Cmp >
  void insertionSort(BiDirIterator first, BiDirIterator last, Cmp cmp)
  {
    using iter_t = BiDirIterator;
    for (iter_t i = std::next(first); i != last; ++i)
    {
      auto val = *i;
      iter_t j = i;
      while (j != first && cmp(val, *std::prev(j)))
      {
          *j = *std::prev(j);
          --j;
      }
      *j = val;
  }
}


  template< typename RandomAccessIterator, typename Cmp >
  void quickSort(RandomAccessIterator first, RandomAccessIterator last, Cmp cmp) {
    size_t dist = std::distance(first, last);
    if (dist <= 1)
    {
      return;
    }
    using iter_t = RandomAccessIterator;
    iter_t pivot = first + dist / 2;
    auto pivotVal = *pivot;

    iter_t left = first;
    iter_t right = last - 1;
    while (left <= right)
    {
      while (cmp(*left, pivotVal))
      {
        ++left;
      }
      while (cmp(pivotVal, *right))
      {
        --right;
      }
      if (left <= right)
      {
        std::iter_swap(left, right);
        ++left;
        --right;
      }
    }

    quickSort(first, right + 1, cmp);
    quickSort(left, last, cmp);
  }
}

#endif

