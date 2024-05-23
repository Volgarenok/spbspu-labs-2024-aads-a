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
      auto pivot = begin + (end - begin) / 2;
      while (begin <= end)
      {
        while (cmp(*begin, *pivot))
        {
          begin++;
        }
        while (cmp(*pivot, *end))
        {
          end--;
        }
        if (begin >= end)
        {
          break;
        }
        std::swap(*(begin++), *(end--));
        ++begin;
      }
      return end;

      //return (begin + (end - begin) / 2);
    }
  }

  template< class RandomAccessIt, class Compare >
  void doQuickSort(RandomAccessIt begin, RandomAccessIt end, Compare cmp)
  {
    if (begin < end)
    {
      auto pivot = detail::partition(begin, end, cmp);
      doQuickSort(begin, pivot, cmp);
      doQuickSort(std::next(pivot), end, cmp);
    }
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
