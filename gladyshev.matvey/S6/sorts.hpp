#ifndef SORTS_HPP
#define SORTS_HPP

#include <algorithm>
#include <iterator>

namespace gladyshev
{
  template< typename Compare, typename Iter >
  void selection(Iter begin, Iter end, Compare cmp)
  {
    for (Iter it1 = begin; it1 != end; ++it1)
    {
      Iter min = it1;
      for (Iter it2 = it1; it2 != end; ++it2)
      {
        if (cmp(*it2, *min))
        {
          min = it2;
        }
      }
      std::swap(*it1, *min);
    }
  }
  template< typename Compare, typename Iter >
  void inplaceMerge(Iter first, Iter mid, Iter last, Compare cmp)
  {
    while (first != mid && mid != last)
    {
      if (cmp(*mid, *first))
      {
        std::rotate(first, mid, std::next(mid));
        ++mid;
      }
      else
      {
        ++first;
      }
    }
  }
  template< typename Compare, typename Iter >
  void merge(Iter begin, Iter end, Compare cmp)
  {
    auto size = std::distance(begin, end);
    if (size > 1)
    {
      Iter mid = begin;
      std::advance(mid, size / 2);
      merge(begin, mid, cmp);
      merge(mid, end, cmp);
      inplaceMerge(begin, mid, end, cmp);
    }
  }
}

#endif
