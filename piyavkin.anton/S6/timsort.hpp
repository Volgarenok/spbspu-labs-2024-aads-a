#ifndef TIMSORT_HPP
#define TIMSORT_HPP
#include <cstddef>
#include <utility>

namespace piyavkin
{
  namespace detail
  {
    size_t get_min_size(size_t n)
    {
      size_t end_one = 0;
      while (n > 64)
      {
        end_one |= n & 1;
        n >>= 1;
      }
      return n + end_one;
    }
    template< class RandIt, class Cmp >
    void sort_ins(RandIt begin, size_t n, Cmp cmp)
    {
      for (size_t i = 1; i != n; ++i)
      {
        RandIt temp = begin + i;
        size_t j = i;
        while (j > 0 && cmp(temp[i], temp[i + 1]))
        {
          std::swap(temp[i], temp[i + 1]);
          --j;
        }
      }
    }
    template< class RandIt, class Cmp >
    size_t find_subarr(RandIt begin, Cmp cmp, size_t max_size)
    {
      size_t count = 0;
      while (max_size > count && cmp(*begin, *(begin + 1)))
      {
        ++begin;
        ++count;
      }
      if (count == 0)
      {
        while (max_size > count && !cmp(*begin, *(begin + 1)))
        {
          ++begin;
          ++count;
        }
        sort_ins(begin - count, begin, cmp);
      }
      return count;
    }
  }
  template< class RandIt, class Cmp >
  void timsort(RandIt it, size_t n, Cmp cmp)
  {
    size_t size_min = detail::get_min_size(n);
    size_t pass = 0;
    RandIt start = it;
    while (pass < n - 1)
    {
      pass += detail::find_subarr(start, cmp, n);
      start += pass;
    }
  }
}
#endif