#ifndef SORTS_HPP
#define SORTS_HPP

#include <list>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include "outputInput.hpp"

namespace sivkov
{
  template < typename ForwardIt, typename Compare >
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

  template < typename RandomIt, typename Compare >
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
  template< typename T >
  void enterTypeOfSort(const std::string& type, std::deque< T >& deq, List< T >& fwdList, std::list< T >& biList, std::ostream& out)
  {
    std::list< T > biList2 = biList;
    std::deque< T > deq2 = deq;
    std::deque< T > deq3 = deq;
    if (type == "ascending")
    {
      oddEvenSort(fwdList.cbegin(), fwdList.cend(), std::less< T >());
      shellSort(biList.begin(), biList.end(), std::less< T >());
      biList2.sort(std::less< T >());
      oddEvenSort(deq.begin(), deq.end(), std::less< T >());
      shellSort(deq2.begin(), deq2.end(), std::less< T >());
      std::sort(deq3.begin(), deq3.end(), std::less< T >());
    }
    else if (type == "descending")
    {
      oddEvenSort(fwdList.cbegin(), fwdList.cend(), std::greater< T >());
      shellSort(biList.begin(), biList.end(), std::greater< T >());
      biList2.sort(std::greater< T >());
      oddEvenSort(deq.begin(), deq.end(), std::greater< T >());
      shellSort(deq2.begin(), deq2.end(), std::greater< T >());
      std::sort(deq3.begin(), deq3.end(), std::greater< T >());
    }
    else
    {
      throw std::invalid_argument("Error type of sort");
    }
    print(out, fwdList);
    print(out, biList);
    print(out, biList2);
    print(out, deq);
    print(out, deq2);
    print(out, deq3);
  }
}
#endif
