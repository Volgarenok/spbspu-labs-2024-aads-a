#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <list>

#include "list.hpp"

namespace belokurskaya
{
  template <typename It, class Cmp>
  void shakerSort(It begin, It end, Cmp cmp)
  {
    bool swapped = true;

    while (swapped)
    {
      swapped = false;

      for (auto it = begin; it != std::prev(end); ++it)
      {
        if (cmp(*std::next(it), *it))
        {
          std::swap(*it, *std::next(it));
          swapped = true;
        }
      }
      if (!swapped)
      {
        break;
      }

      swapped = false;

      for (auto it = std::prev(end); it != begin; --it)
      {
        if (cmp(*it, *std::prev(it)))
        {
          std::swap(*it, *std::prev(it));
          swapped = true;
        }
      }
    }
  }

  template< class Iter, class Compare >
  Iter getPivot(Iter begin, Iter end, Compare cmp)
  {
    auto pivot = begin;
    auto iter = std::next(begin);
    while (iter != end)
    {
      if (!cmp(*pivot, *iter))
      {
        auto temp_iter = pivot;
        using T = typename Iter::value_type;
        T temp(std::move(*iter));
        while (temp_iter != std::next(iter))
        {
          std::swap(*temp_iter, temp);
          ++temp_iter;
        }
        ++pivot;
      }
      ++iter;
    }
    return pivot;
  }

  template < class T, class Compare >
  void quickSort(T begin, T end, Compare cmp)
  {
    if (begin != end)
    {
      auto pivot = getPivot(begin, end, cmp);
      quickSort(begin, pivot, cmp);
      quickSort(std::next(pivot), end, cmp);
    }
  }
}

#endif
