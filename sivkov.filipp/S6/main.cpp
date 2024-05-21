#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <list.hpp>

void oddEvenSort(ForwardIt first, ForwardIt last, Compare comp)
{
  if (first == last) return;

  bool sorted = false;

  while (!sorted)
  {
    sorted = true;
    ForwardIt it = first;
    ForwardIt next = it;
    ++next;

    while (next != last)
    {
      if (comp(*next, *it))
      {
        std::swap(*it, *next);
        sorted = false;
      }
      if (next != last)
      {
        ++next;
        if (next != last)
        {
          ++it;
        }
      }
    }
    it = first;
    next = it;
    while (next != last)
    {
      if (comp(*next, *it))
      {
        std::swap(*it, *next);
        sorted = false;
      }
      if (next != last)
      {
        ++next;
        if (next != last)
        {
          ++it;
        }
      }
    }
  }
}

int main()
{
}
