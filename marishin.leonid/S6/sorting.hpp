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
    ++begin;
    size_t leftMark = 1;
    size_t rightMark = size - 1;
    auto end = begin;
    size_t count = 0;
    for (size_t i = 1; i < size - 1; ++i)
    {
      ++end;
    }
    while (leftMark <= rightMark)
    {
      auto tempEnd = end;
      auto tempBegin = begin;
      for (size_t i = 0; i < count; i++)
      {
        --tempEnd;
        ++tempBegin;
      }
      auto tmpBegin = tempBegin;
      for (size_t i = rightMark; i >= leftMark; --i)
      {
        auto curr = tempEnd;
        --curr;
        if (cmp(*(tempEnd), *(curr)))
        {
          std::iter_swap(curr, tempEnd);
        }
        --tempEnd;
      }
      leftMark++;
      tmpBegin++;

      for (size_t i = leftMark; i <= rightMark; ++i)
      {
        auto curr = tmpBegin;
        --curr;
        if (cmp(*(tmpBegin), *(curr)))
        {
          std::iter_swap(curr, tmpBegin);
        }
        ++tmpBegin;
      }
      rightMark--;
      count++;
    }
  }

  template< class Iterator, class Compare >
  void qSort(Iterator begin, size_t size, Compare cmp)
  {
    if (size < 2)
    {
      return;
    }
    Iterator pivot = begin + size / 2;

    Iterator left = begin;
    Iterator right = begin + size - 1;
    while (left <= right)
    {
      while (cmp(*(left), *(pivot)))
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
    if (right > begin)
    {
      qSort(begin, right - begin + 1, cmp);
    }
    if (left < begin + size)
    {
      qSort(left, begin + size - left, cmp);
    }
  }

}
#endif
