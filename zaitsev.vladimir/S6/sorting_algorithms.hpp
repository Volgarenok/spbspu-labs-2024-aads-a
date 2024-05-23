#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP
#include <iterator>
#include <algorithm>

template< class ForwardIt, class Comapare >
void shellSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t size = 0)
{
  if (size == 0)
  {
    ForwardIt copy = begin;
    while (copy != end)
    {
      ++size;
      ++copy;
    }
  }
  size_t diff = size;
  while (diff > 1)
  {
    diff /= 2;
    ForwardIt front_start = begin;
    std::advance(front_start, diff);
    size_t swaps = 1;
    while (swaps != 0)
    {
      ForwardIt front = front_start;
      ForwardIt back = begin;
      swaps = 0;
      while (front != end)
      {
        if (cmp(*front, *back))
        {
          std::swap(*back, *front);
          ++swaps;
        }
        ++front;
        ++back;
      }
    }
  }
}

template< class ForwardIt, class Comapare >
void bucketSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t buckets_nmb = 10)
{
  using T = typename ForwardIt::value_type;
  if (begin == end)
  {
    return;
  }
  size_t size = 1;
  T max_val = *begin;
  T min_val = *begin;
  bool is_sorted = false;
  ForwardIt cur = begin;
  ForwardIt pre_cur = begin;
  ++cur;
  while (cur != end)
  {
    min_val = cmp(*cur, min_val) ? *cur : min_val;
    max_val = cmp(max_val, *cur) ? *cur : max_val;
    is_sorted |= !cmp(*cur, *pre_cur);
    ++size;
    ++cur;
    ++pre_cur;
  }


}

#endif

