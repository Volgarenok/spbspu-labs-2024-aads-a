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
      auto pivot = begin;
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
      }
      return end;
    }
  }

  template< class RandomAccessIt, class Compare >
  void doQuicksort(RandomAccessIt begin, RandomAccessIt end, Compare cmp)
  {
    if (begin < end)
    {
      auto pivot = detail::partition(begin, end, cmp);
      doQuicksort(begin, pivot, cmp);
      doQuicksort(std::next(pivot), end, cmp);
    }
  }

  namespace detail
  {
    template< class RandomAccessIt, class Compare >
    void doInsertsort(RandomAccessIt begin, RandomAccessIt end, Compare cmp)
    {
      if (begin == end)
      {
        return;
      }
      auto cur_iter = std::next(begin);
      while (cur_iter != end)
      {
        auto temp_iter = cur_iter;
        auto start = std::prev(cur_iter);
        while (start != begin)
        {
          if (cmp(*temp_iter, *start))
          {
            std::swap(*temp_iter, *start);
            --temp_iter;
          }
          else
          {
            break;
          }
          start--;
        }
        ++cur_iter;
      }
    }
  }

  template< class RandomAccessIt, class Compare >
  void doTimsort(RandomAccessIt begin, size_t size, Compare cmp)
  {
    if (size == 0)
    {
      return;
    }
    size_t step = 0;
    size_t n = size;
    while (n >= 64)
    {
      step |= n & 1;
      n = n >> 1;
    }
    step = n + step;
    for (size_t i = 0; i < size; i += step)
    {

    }
    //std::sort(begin, end, cmp);
  }

  template< class BidirectionalIt, class Compare >
  void sort1(BidirectionalIt begin, BidirectionalIt end, Compare cmp)
  {
    std::sort(begin, end, cmp);
  }
}

#endif
