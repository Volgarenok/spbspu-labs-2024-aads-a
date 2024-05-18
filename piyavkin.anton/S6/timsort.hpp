#ifndef TIMSORT_HPP
#define TIMSORT_HPP
#include <cstddef>

namespace piyavkin
{
  namespace detail
  {
    size_t get_min_size(size_t n)
    {
      bool is_no_power_of_two = false;
      while (n > 64)
      {
        if (n % 2 != 0)
        {
          is_no_power_of_two = true;
        }
        n /= 2;
      }
      return n + is_no_power_of_two;
    }
  }
  template< class RandIt, class Cmp >
  void timsort(RandIt it, size_t n, Cmp cmp)
  {
    size_t size_min = detail::get_min_size(n);
  }
}
#endif