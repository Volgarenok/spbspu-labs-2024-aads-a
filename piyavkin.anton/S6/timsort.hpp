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
    void sort_ins(RandIt begin, RandIt end, Cmp cmp)
    {
      RandIt start = ++begin;
      for (; start != end; ++start)
      {
        RandIt temp = start--;
        while (start != begin && cmp(*temp, *start))
        {
          std::swap(temp, start);
          --start;
        }
        ++start;
      }
    }
  }
  template< class RandIt, class Cmp >
  void timsort(RandIt it, size_t n, Cmp cmp)
  {
    size_t size_min = detail::get_min_size(n);
  }
}
#endif