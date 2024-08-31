#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <list>

#include "list.hpp"

namespace belokurskaya
{
  template < typename T >
  void shakerSort(std::list< T >& list)
  {
    bool swapped = true;
    auto begin = list.begin();
    auto end = list.end();

    while (swapped)
    {
      swapped = false;

      for (auto it = begin; it != end; ++it)
      {
        if (std::next(it) != end && *it > *std::next(it))
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
        if (*it < *std::prev(it))
        {
          std::swap(*it, *std::prev(it));
          swapped = true;
        }
      }
    }
  }

  
  template< class T, class Compare >
  T getPivot(T begin, T end, Compare cmp)
  {
    auto pivot = begin;
    auto iter = std::next(begin);
    while (iter != end)
    {
      if (!cmp(*pivot, *iter))
      {
        auto temp_iter = pivot;
        using T = typename T::value_type;
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
  void quicksort(T begin, T end, Compare cmp)
  {
    if (begin != end)
    {
      auto pivot = getPivot(begin, end, cmp);
      quicksort(begin, pivot, cmp);
      quicksort(std::next(pivot), end, cmp);
    }
  }

  template < typename T >
  void bubbleSort(List< T >& list)
  {
    bool swapped = true;
    auto end = list.end();

    while (swapped)
    {
      swapped = false;

      for (auto it = list.begin(); it != end; ++it)
      {
        if (it != end && *it > *(it + 1))
        {
          std::swap(*it, *(it + 1));
          swapped = true;
        }
      }
    }
  }
}

#endif
