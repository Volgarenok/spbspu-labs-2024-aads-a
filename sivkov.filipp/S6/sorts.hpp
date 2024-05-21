#ifndef SORTS_HPP
#define SORTS_HPP

#include <algorithm>
#include <iterator>

template <typename ForwardIt, typename Compare>
void oddEvenSort(ForwardIt first, ForwardIt last, Compare comp)
{
  if (first == last)
  {
    return;
  }
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


template <typename RandomIt, typename Compare>
void shellSort(RandomIt first, RandomIt last, Compare comp)
{
  auto n = std::distance(first, last);

  for (auto gap = n / 2; gap > 0; gap /= 2)
  {
    for (auto i = first; std::distance(first, i) < n; ++i)
    {
      auto tempIt = i;
      for (auto j = tempIt; std::distance(first, j) >= gap; std::advance(j, -gap))
      {
        auto prevGapIt = j;
        std::advance(prevGapIt, -gap);

        if (comp(*tempIt, *prevGapIt))
        {
          std::swap(*tempIt, *prevGapIt);
          tempIt = prevGapIt;
        }
        else
        {
          break;
        }
      }
    }
  }
}

#endif

