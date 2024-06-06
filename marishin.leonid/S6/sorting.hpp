#ifndef SORTING_HPP
#define SORTING_HPP
#include <utility>
#include <algorithm>
#include <iterator>
#include <iterator.hpp>
#include <linkedList.hpp>

namespace marishin
{
  template < class Iterator, class Compare >
  void shaker(Iterator begin, size_t size, Compare cmp)
  {
    if (size <= 1)
    {
      return;
    }
    size_t leftMark = 0;
    size_t rightMark = size - 1;

    while (leftMark <= rightMark)
    {
      for (size_t i = rightMark; i > leftMark; --i)
      {
        Iterator curr = std::next(begin, i);
        Iterator prev = std::prev(curr);
        if (cmp(*curr, *prev))
        {
          std::iter_swap(curr, prev);
        }
      }
      ++leftMark;

      for (size_t i = leftMark; i <= rightMark; ++i)
      {
        Iterator curr = std::next(begin, i);
        Iterator prev = std::prev(curr);
        if (cmp(*curr, *prev))
        {
          std::iter_swap(curr, prev);
        }
      }
      --rightMark;
    }
  }

  template< class Iterator, class Compare >
  void qSort(Iterator begin, size_t size, Compare cmp)
  {
    if (size < 2)
    {
      return;
    }
    Iterator pivot = std::next(begin, size / 2);

    Iterator left = begin;
    Iterator right = std::next(begin, size - 1);
    while (left <= right)
    {
      while (cmp(*left, *pivot))
      {
        ++left;
      }
      while (cmp(*pivot, *right))
      {
        --right;
      }
      if (left <= right)
      {
        std::iter_swap(left, right);
        ++left;
        --right;
      }
    }
    if (right >= begin)
    {
      qSort(begin, std::distance(begin, right) + 1, cmp);
    }
    if (left < std::next(begin, size))
    {
      qSort(left, std::distance(left, std::next(begin, size)), cmp);
    }
  }
}
#endif
