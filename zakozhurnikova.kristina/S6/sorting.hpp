#ifndef SORTING_HPP
#define SORTING_HPP
#include <utility>
#include <algorithm>
#include <iterator.hpp>
#include <list.hpp>

namespace zakozhurnikova
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

  template < class Iterator, class Compare >
  void shell(Iterator begin, size_t size, Compare cmp)
  {
    auto spacing = begin + size / 2;
    for (size_t interval = size / 2; interval > 0; interval /= 2)
    {
      auto temp = begin + interval;
      for (size_t i = interval; i < size; ++i)
      {
        auto number = *temp;
        auto tmp = temp;
        size_t j = i;
        for (; j >= interval && cmp(number, *(tmp - interval)); j -= interval)
        {
          auto next = tmp - interval;
          *tmp = *next;
          tmp = next;
        }
        *tmp = number;
        ++temp;
      }
      spacing = begin + interval / 2;
    }
  }
}
#endif
