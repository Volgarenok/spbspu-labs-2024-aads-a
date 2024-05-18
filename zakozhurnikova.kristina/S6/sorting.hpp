#ifndef SORTING_HPP
#define SORTING_HPP
#include <iterator.hpp>
#include <list.hpp>
#include <utility>

namespace zakozhurnikova
{
  template < class Iterator, class Compare >
  void shaker(Iterator& begin, size_t size, Compare cmp)
  {
    int leftMark = 1;
    int rightMark = size - 1;
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
      for (int i = rightMark; i >= leftMark; --i)
      {
        auto curr = tempEnd;
        --curr;
        if (cmp(*(tempEnd), *(curr)))
        {
          std::swap(*curr, *tempEnd);
        }
        --tempEnd;
      }
      leftMark++;
      tmpBegin++;

      for (int i = leftMark; i <= rightMark; ++i)
      {
        auto curr = tmpBegin;
        --curr;
        if (cmp(*(tmpBegin), *(curr)))
        {
          int buff;
          buff = *curr;
          *curr = *tmpBegin;
          *tmpBegin = buff;
        }
        ++tmpBegin;
      }
      rightMark--;
      count++;
    }
  }

  template < class Iterator, class Compare >
  void shell(Iterator begin, size_t s, Compare cmp)
  {
    int size = s;
    auto spacing = begin + size / 2;
    for (int interval = size / 2; interval > 0; interval /= 2)
    {
      auto temp = begin + interval;
      for (int i = interval; i < size; ++i)
      {
        auto number = *temp;
        auto tmp = temp;
        int j = i;
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
