#ifndef SORTING_HPP
#define SORTING_HPP
#include <utility>
#include <iterator>
#include <algorithm>

namespace marishin
{
  template< class Iterator >
  Iterator findPivot(Iterator begin, Iterator end)
  {
    --end;
    while (begin < end)
    {
      ++begin;
      --end;
    }
    return begin;
  }

  template< class Iterator, class Compare >
  void QSort(Iterator begin, Iterator end, Compare cmp)
  {
    Iterator toSwap = findPivot(begin, end);
    Iterator pivot = end;
    --pivot;
    std::iter_swap(toSwap, pivot);

    Iterator first = begin;
    Iterator second = begin;
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

  template < class Iterator, class Compare >
  void shaker(Iterator begin, Iterator end, Compare cmp)
  {
    auto last = std::prev(end);
    bool swapped = true;
    while (swapped)
    {
      swapped = false;
      for (auto i = begin; i != last; i++)
      {
        auto next = std::next(i);
        if (!cmp(*i, *next))
        {
          std::swap(*i, *next);
          swapped = true;
        }
      }
      last = std::prev(last);
      if (!swapped)
      {
        break;
      }
      swapped = false;
      for (auto i = last; i != begin; --i)
      {
        auto prev = std::prev(i);
        if (cmp(*i, *prev))
        {
          std::swap(*i, *prev);
          swapped = true;
        }
      }
      begin = std::next(begin);
    }
  }
}
#endif
