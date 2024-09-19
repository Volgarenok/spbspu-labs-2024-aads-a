#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include <iterator>
#include <iostream>
#include <algorithm>
#include <utility>

namespace baranov
{
  namespace detail
  {
    template <typename FwdIterator, typename Cmp>
    FwdIterator partition(FwdIterator first, FwdIterator last, Cmp cmp)
    {
      auto pivot = *first;
      FwdIterator left = first;
      FwdIterator right = std::next(first);
      while (right != last)
      {
        if (cmp(*right, pivot))
        {
          ++left;
          std::iter_swap(left, right);
        }
        ++right;
      }
      std::iter_swap(first, left);
      return left;
    }
  }

  template <typename FwdIterator, typename Cmp>
  void quickSort(FwdIterator first, FwdIterator last, Cmp cmp)
  {
    if (first == last || std::next(first) == last)
    {
      return;
    }
    FwdIterator pivot = detail::partition(first, last, cmp);
    quickSort(first, pivot, cmp);
    quickSort(std::next(pivot), last, cmp);
  }

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
}

#endif

