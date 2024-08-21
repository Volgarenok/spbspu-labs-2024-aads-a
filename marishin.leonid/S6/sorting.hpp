#ifndef SORTING_HPP
#define SORTING_HPP
#include <utility>
#include <iterator>
#include <algorithm>

namespace marishin
{
  template< class Iterator, class Compare >
  Iterator findPivot(Iterator begin, Iterator end, Compare cmp)
  {
    auto pivot = begin;
    auto cur_iter = std::next(begin);
    while (cur_iter != end)
    {
      if (!cmp(*pivot, *cur_iter))
      {
        auto temp_iter = pivot;
        using T = typename Iterator::value_type;
        T temp(std::move(*cur_iter));
        while (temp_iter != std::next(cur_iter))
        {
          std::swap(*temp_iter, temp);
          ++temp_iter;
        }
        ++pivot;
      }
      ++cur_iter;
    }
    return pivot;
  }

  template< class Iterator, class Compare >
  void QSort(Iterator begin, Iterator end, Compare cmp)
  {
    if (begin != end)
    {
      auto pivot = findPivot(begin, end, cmp);
      QSort(begin, pivot, cmp);
      QSort(std::next(pivot), end, cmp);
    }
  }


  template < class Iterator, class Compare >
  void shaker(Iterator begin, Iterator end, Compare cmp)
  {
    auto last = std::prev(end);
    bool swapped = true;
    while (swapped)
    {
      swapped = false;
      for (auto i = begin; i != last; i++)
      {
        auto next = std::next(i);
        if (!cmp(*i, *next))
        {
          std::swap(*i, *next);
          swapped = true;
        }
      }
      last = std::prev(last);
      if (!swapped)
      {
        break;
      }
      swapped = false;
      for (auto i = last; i != begin; --i)
      {
        auto prev = std::prev(i);
        if (cmp(*i, *prev))
        {
          std::swap(*i, *prev);
          swapped = true;
        }
      }
      begin = std::next(begin);
    }
  }
}
#endif
