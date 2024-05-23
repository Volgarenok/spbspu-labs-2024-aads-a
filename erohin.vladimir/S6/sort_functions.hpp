#ifndef SORT_FUNCTIONS_HPP
#define SORT_FUNCTIONS_HPP

#include <algorithm>
#include <iterator>

namespace erohin
{
  namespace detail
  {
    template< class RandomAccessIt, class Compare >
    RandomAccessIt partition(RandomAccessIt begin, RandomAccessIt end, Compare cmp)
    {
      auto pivot = end;
      auto iter = std::prev(begin);
      while (begin != std::prev(end))
      {
        if (cmp(*begin, *pivot))
        {
          iter++;
          if (iter != begin)
          {
            std::swap(*begin, *begin);
          }
        }
        ++begin;
      }
      std::swap(*std::next(iter), *end);
      return std::next(iter);
    }
  }

  template< class RandomAccessIt, class Compare >
  void doQuickSort(RandomAccessIt begin, RandomAccessIt end, Compare cmp)
  {
    if (begin >= end)
    {
      return;
    }
    auto pivot = detail::partition(begin, end, cmp);
    doQuickSort(begin, pivot, cmp);
    doQuickSort(pivot, end, cmp);
  }

  template< class BidirectionalIt, class Compare >
  void sort2(BidirectionalIt begin, BidirectionalIt end, Compare cmp)
  {
    std::sort(begin, end, cmp);
  }

  template< class BidirectionalIt, class Compare >
  void sort1(BidirectionalIt begin, BidirectionalIt end, Compare cmp)
  {
    std::sort(begin, end, cmp);
  }
}

#endif
