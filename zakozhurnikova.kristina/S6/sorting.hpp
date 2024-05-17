#ifndef SORTING_HPP
#define SOTRING_HPP
#include <iterator.hpp>
#include <list.hpp>
#include <utility>

using namespace zakozhurnikova;

template < class Iterator >
void shaker(Iterator& begin, size_t size)
{
  int leftMark = 1;
  int rightMark = size - 1;
  auto end = begin;
  size_t count = 0;
  for (size_t i = 2; i < size; ++i)
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
      if (*(curr) > *(tempEnd))
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
      if (*(curr) > *(tmpBegin))
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

#endif
