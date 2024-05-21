#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <iterator>
#include <algorithm> 

namespace novokhatskiy
{
  template< class Iter, class P >
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

  template< class It, class P >
  void doInsertionSort(It begin, It end, P cmp)
  {
    for (auto i = begin; i != end; i++)
    {
      for (auto j = begin; j != i; j++)
      {
        if (cmp(*i,*j))
        {
          std::swap(*i, *j);
        }
      }
    }
    /*auto it = std::next(begin);
    while (it != end)
    {
      auto key = *it;
      auto prev = std::prev(it);
      while (prev != begin && cmp(*prev, key))
      {
        *it = *prev;
        it = prev;
        prev = std::prev(it);
      }
      if (!cmp(key, *prev))
      {
        *it = key;
      }
      
      it = std::next(it);
    }*/
  }


}

#endif
