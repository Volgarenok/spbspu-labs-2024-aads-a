#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <utility>
#include <algorithm>

namespace nikitov
{
  template< class BiIterator, class Compare >
  void oddEvenSort(BiIterator begin, BiIterator end, Compare cmp)
  {
    bool isOdd = true;
    bool isSorted = false;
    while (!isSorted || isOdd)
    {
      BiIterator first = begin;
      BiIterator second = begin;
      ++second;
      if (!isOdd)
      {
        ++first;
        ++second;
      }
      isOdd = !isOdd;

      isSorted = true;
      while (second != end)
      {
        if (!cmp(*first, *second))
        {
          isSorted = false;
          std::iter_swap(first, second);
        }
        ++first;
        ++second;
      }
    }
  }

  template< class RandIterator >
  RandIterator findPivot(RandIterator begin, RandIterator end)
  {
    --end;
    while (begin < end)
    {
      ++begin;
      --end;
    }
    return begin;
  }

  template< class RandIterator, class Compare >
  void QSort(RandIterator begin, RandIterator end, Compare cmp)
  {
    RandIterator toSwap = findPivot(begin, end);
    RandIterator pivot = end;
    --pivot;
    std::iter_swap(toSwap, pivot);

    RandIterator first = begin;
    RandIterator second = begin;
    bool isFirst = true;
    while (second != pivot)
    {
      if (cmp(*second, *pivot))
      {
        if (isFirst)
        {
          isFirst = false;
        }
        else
        {
          ++first;
        }
        std::iter_swap(first, second);
      }
      ++second;
    }

    if (!isFirst)
    {
      ++first;
    }
    std::iter_swap(first, pivot);
    if (first != begin)
    {
      QSort(begin, first, cmp);
    }
    if (first != pivot)
    {
      QSort(++first, end, cmp);
    }
  }
}
#endif
