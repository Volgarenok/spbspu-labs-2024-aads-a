#ifndef SORTING_HPP
#define SOTRING_HPP
#include <iterator.hpp>
#include <list.hpp>
#include <utility>

using namespace zakozhurnikova;

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
    auto tmpEnd = tempEnd;
    auto tmpBegin = tempBegin;
    for (int i = rightMark; i >= leftMark; --i)
    {
      auto curr = tempEnd;
      --curr;
      if (cmp(*(curr), *(tempEnd)))
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
      if (cmp(*(curr), *(tmpBegin)))
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

template< class Iterator >
void shell(Iterator begin, size_t size)
{
  auto spacing = begin + size / 2;
  for (size_t gap = size / 2; gap > 0; gap /= 2)
  {
    auto temp = spacing;
    for (size_t i = gap; i < size; ++i)
    {
      auto number = temp;
//      int temp = arr[i];
      auto tmp = temp;
      size_t j = i;
      for (; j >= gap && *(tmp - gap) > *number; j -= gap)
      {
        *tmp = *(tmp - gap);
//        arr[j] = arr[j - gap];
        tmp = tmp - gap;
      }
//      arr[j] = temp;
      *tmp = *number;
    ++temp;
    }
  spacing = begin + gap / 2;
  }
}

#endif
