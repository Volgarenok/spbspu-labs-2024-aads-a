#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include <iterator>

namespace baranov
{
  template< typename BiDirIterator, typename Cmp >
  void insertionSort(BiDirIterator first, BiDirIterator last, Cmp cmp)
  {
    using iter_t = BiDirIterator;
    for (iter_t i = std::next(first); i != last; ++i)
    {
      auto val = *i;
      iter_t j = std::prev(i);
      for (; j != last && !cmp(*j, val); --j)
      {
        *(std::next(j)) = *j;
      }
      *(++j) = val;
    }
  }

  template< typename BiDirIterator, typename Cmp >
  void quickSort(BiDirIterator first, BiDirIterator last, Cmp cmp) {
    size_t distance = std::distance(first, last);
    if (distance <= 1)
    {
      return;
    }
    BiDirIterator pivot = first;
    for (size_t i = 0; i < distance / 2; ++i)
    {
      ++pivot;
    }
    auto pivotVal = *pivot;

    BiDirIterator left = first;
    BiDirIterator right = std::prev(last);
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

    quickSort(first, right, cmp);
    quickSort(left, last, cmp);
  }
}
#endif

