#ifndef SORTING_HPP
#define SOTRING_HPP
#include <iterator.hpp>
#include <list.hpp>

using namespace zakozhurnikova;

template < class Iterator >
void swap(Iterator right, Iterator left)
{
  int buff;
  buff = *left;
  *left = *right;
  *right = buff;
}

template < class Iterator >
void shaker(Iterator& begin, size_t size)
{
  int leftMark = 1;
  int rightMark = size - 1;
  auto end = begin;
  for (size_t i = 1; i < size; ++i)
  {
    ++end;
  }
  while (leftMark <= rightMark)
  {
    auto tempEnd = end;
    auto tempBegin = begin;
    for (int i = rightMark; i >= leftMark; --i)
    {
      auto curr = tempEnd;
      --curr;
      if (*(curr) > *(tempEnd))
      {
        int buff;
        buff = *curr;
        *curr = *tempEnd;
        *tempEnd = buff;
      }
      --tempEnd;
    }
    leftMark++;
    tempBegin++;

    for (int i = leftMark; i <= rightMark; ++i)
    {
      auto curr = tempBegin;
      --curr;
      if (*(curr) > *(tempBegin))
      {
        int buff;
        buff = *curr;
        *curr = *tempEnd;
        *tempEnd = buff;
      }
      ++tempBegin;
    }
    rightMark--;
    tempEnd--;
  }
}

#endif
