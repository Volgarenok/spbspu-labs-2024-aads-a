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

template <typename ForwardIt, typename Compare>
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

int main()
{
  using namespace sivkov;
  List< int > fwdList;
  fwdList.push_back(7);
  fwdList.push_back(9);
  fwdList.push_back(1);
  fwdList.push_back(4);
  fwdList.push_back(8);
  fwdList.push_back(6);
  fwdList.push_back(3);
  fwdList.push_back(10);
  fwdList.push_back(2);
  fwdList.push_back(5);
  fwdList.push_back(11);


  oddEvenSort(fwdList.begin(), fwdList.end(), std::less<int>());

  for (const auto& el : fwdList)
  {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  std::list< int > biList2;
  biList2.push_back(7);
  biList2.push_back(9);
  biList2.push_back(1);
  biList2.push_back(4);
  biList2.push_back(8);
  biList2.push_back(6);
  biList2.push_back(3);
  biList2.push_back(10);
  biList2.push_back(2);
  biList2.push_back(5);
  biList2.push_back(11);

  shellSort(biList2.begin(), biList2.end(), std::less< int >());

  for (const auto& el : biList2)
  {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  std::list< int > biList;
  biList.push_back(7);
  biList.push_back(9);
  biList.push_back(1);
  biList.push_back(4);
  biList.push_back(8);
  biList.push_back(6);
  biList.push_back(3);
  biList.push_back(10);
  biList.push_back(2);
  biList.push_back(5);
  biList.push_back(11);

  biList.sort(std::less< int >());

  for (const auto& el : biList)
  {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  std::deque< int > deq1;
  deq1.push_back(7);
  deq1.push_back(9);
  deq1.push_back(1);
  deq1.push_back(4);
  deq1.push_back(8);
  deq1.push_back(6);
  deq1.push_back(3);
  deq1.push_back(10);
  deq1.push_back(2);
  deq1.push_back(5);
  deq1.push_back(11);

  std::deque< int > deq2;
  deq2.push_back(7);
  deq2.push_back(9);
  deq2.push_back(1);
  deq2.push_back(4);
  deq2.push_back(8);
  deq2.push_back(6);
  deq2.push_back(3);
  deq2.push_back(10);
  deq2.push_back(2);
  deq2.push_back(5);
  deq2.push_back(11);

  std::deque< int > deq3;
  deq3.push_back(7);
  deq3.push_back(9);
  deq3.push_back(1);
  deq3.push_back(4);
  deq3.push_back(8);
  deq3.push_back(6);
  deq3.push_back(3);
  deq3.push_back(10);
  deq3.push_back(2);
  deq3.push_back(5);
  deq3.push_back(11);

  oddEvenSort(deq1.begin(), deq1.end(), std::less< int >());
  shellSort(deq2.begin(), deq2.end(), std::less< int >());
  std::sort(deq3.begin(), deq3.end(), std::less< int >());
  for (const auto& el : deq1)
  {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  for (const auto& el : deq2)
  {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  for (const auto& el : deq3)
  {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  return 0;
}
