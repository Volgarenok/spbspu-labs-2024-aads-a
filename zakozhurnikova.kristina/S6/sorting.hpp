#ifndef SORTING_HPP
#define SOTRING_HPP
#include <list.hpp>
#include <iterator.hpp>

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
void shaker(Iterator& begin, Iterator& end, size_t size)
{
  int leftMark = 1;
  int rightMark = size - 1;
  while (leftMark <= rightMark)
  {
    for (int i = rightMark; i >= leftMark; --i)
    {
      auto curr = end;
      --curr;
      if (*(curr) > *(end))
      {
        int buff;
        buff = *curr;
        *curr = *end;
        *end = buff;
      }
      --end;
    }
    leftMark++;
    begin++;

    for (int i = leftMark; i <= rightMark; ++i)
    {
      auto curr = begin;
      --curr;
      if (*(curr) > *(begin))
      {
        int buff;
        buff = *curr;
        *curr = *end;
        *end = buff;
      }
      ++begin;
    }
    rightMark--;
    end--;
  }
}

#endif
