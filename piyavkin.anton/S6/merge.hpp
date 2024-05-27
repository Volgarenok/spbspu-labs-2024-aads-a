#ifndef MERGE_HPP
#define MERGE_HPP
#include <list.hpp>

namespace piyavkin
{
  namespace detail
  {
    template< class BiIter, class Cmp >
    void merge(BiIter first, BiIter second, BiIter end, Cmp cmp, List< typename BiIter::value_type >& res)
    {
      BiIter border = second;
      while (first != border || second != end)
      {
        if (second == end || (first != border && cmp(*first, *second)))
        {
          res.push_back(*first++);
        }
        else
        {
          res.push_back(*second++);
        }
      }
    }
  }
  template< class BiIter, class Cmp >
  void sort_merge(BiIter begin, size_t size, Cmp cmp)
  {
    List< typename BiIter::value_type > res;
    for (size_t i = 1; i < size; i *= 2)
    {
      BiIter second = begin;
      for (size_t j = 0; j < size - i; j += 2 * i)
      {
        BiIter first = second;
        BiIter border = std::next(first, i);
        second = (j + 2 * i < size) ? std::next(second, 2 * i) : std::next(second, size - j);
        detail::merge(first, border, second, cmp, res);
      }
      std::move(res.begin(), res.end(), begin);
      res.clear();
    }
  }
}
#endif
