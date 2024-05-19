#ifndef TIMSORT_HPP
#define TIMSORT_HPP
#include <cstddef>
#include <utility>
#include <stack.hpp>
#include "merge.hpp"

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
        while (j > 0 && cmp(*temp, *(temp - 1)))
        {
          std::swap(*temp, *temp--);
          --j;
        }
      }
    }
    template< class RandIt, class Cmp >
    size_t find_subarr(RandIt begin, Cmp cmp, size_t max_size)
    {
      size_t count = 1;
      while (max_size > count && cmp(*begin, *(begin + 1)))
      {
        ++begin;
        ++count;
      }
      if (count == 1)
      {
        while (max_size > count && !cmp(*begin, *(begin + 1)))
        {
          ++begin;
          ++count;
        }
        sort_ins(begin - (count - 1), count, cmp);
      }
      return count;
    }
    template< class RandIt, class Cmp >
    void merge_timsort(Stack< std::pair< RandIt, size_t > > stack, Cmp cmp, List< typename RandIt::value_type >& res)
    {
      while (stack.size() > 1)
      {
        std::pair< RandIt, size_t > first_pair = stack.top();
        stack.pop();
        std::pair< RandIt, size_t > second_pair = stack.top();
        stack.pop();
        if (!stack.empty())
        {
          std::pair< RandIt, size_t > third_pair = stack.top();
          stack.pop();
          if (first_pair.second < third_pair.second)
          {
            merge(second_pair.first, first_pair.first, first_pair.first + first_pair.second, cmp, res);
            std::move(res.begin(), res.end(), second_pair.first);
            res.clear();
            second_pair.second += first_pair.second;
            stack.push(third_pair);
            stack.push(second_pair);
          }
          else
          {
            merge(third_pair.first, second_pair.first, second_pair.first + second_pair.second, cmp, res);
            std::move(res.begin(), res.end(), third_pair.first);
            res.clear();
            third_pair.second += second_pair.second;
            stack.push(second_pair);
            stack.push(first_pair);
          }
        }
        else
        {
          merge(second_pair.first, first_pair.first, first_pair.first + first_pair.second, cmp, res);
        }
      }
    }
  }
  template< class RandIt, class Cmp >
  void timsort(RandIt it, size_t n, Cmp cmp)
  {
    size_t size_min = detail::get_min_size(n);
    size_t pass = 0;
    RandIt start = it;
    size_t size_subarr = 0;
    Stack< std::pair< RandIt, size_t > > subarrs;
    while (pass < n)
    {
      size_subarr = detail::find_subarr(start, cmp, n);
      subarrs.push(std::pair< RandIt, size_t >(start, size_subarr));
      start += size_subarr;
      pass += size_subarr;
      if (size_subarr < size_min)
      {
        detail::sort_ins(start, size_min - size_subarr, cmp);
        subarrs.push(std::pair< RandIt, size_t >(start, size_min - size_subarr));
        start += size_min - size_subarr;
        pass += size_min - size_subarr;
      }
    }
    List< typename RandIt::value_type > res;
    detail::merge_timsort(subarrs, cmp, res);
    if (!res.empty())
    {
      std::move(res.begin(), res.end(), it);
    }
  }
}
#endif
