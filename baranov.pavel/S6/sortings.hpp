#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include <iterator>
#include <iostream>
#include <algorithm>
#include <utility>

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

  template <typename BiDirIterator, typename Cmp>
  void quickSort(BiDirIterator first, BiDirIterator last, Cmp cmp)
  {
    size_t dist = std::distance(first, last);
    if (dist <= 1)
    {
      return;
    }
    using iter_t = BiDirIterator;
    iter_t pivot = first;
    std::advance(pivot, dist / 2);

    iter_t left = first;
    iter_t right = first;
    std::advance(right, dist - 1);

    while (left != right)
    {
      while (left != right && !cmp(*pivot, *left))
      {
        ++left;
      }
      while (left != right && cmp(*pivot, *right))
      {
        --right;
      }
      if (left != right)
      {
        std::iter_swap(left, right);
      }
    }
    quickSort(first, right, cmp);
    quickSort(left, last, cmp);
  }
}

#endif

