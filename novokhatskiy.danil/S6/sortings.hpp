#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <algorithm>
#include <iterator>

namespace novokhatskiy
{
  template < class Iter, class P >
  void doShakerSort(Iter begin, Iter end, P cmp)
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

  template < typename It, typename P >
  void doInsertionSort(It begin, It end, P cmp)
  {
    It sorted_end = std::next(begin);

    while (sorted_end != end)
    {
      auto current = sorted_end;

      while (current != begin)
      {
        auto previous = begin;
        It it = begin;
        while (it != current)
        {
          previous = it;
          ++it;
        }

        if (cmp(*current, *previous))
        {
          auto temp = *current;
          *current = *previous;
          *previous = temp;
          current = previous;
        }
        else
        {
          break;
        }
      }
      sorted_end = std::next(sorted_end);
    }
  }
}

#endif
