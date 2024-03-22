#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include "list.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"
#include "inputList.hpp"

int main()
{
  using namespace chistyakov;
  List< std::pair< std::string, List< int > > > list;

  try
  {
    inputList(std::cin, list);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
  }

  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto element = list.begin(); element != list.end(); ++element)
  {
    std::cout << element->first;
    auto next = element;
    if (++next != list.end())
    {
      std::cout << " ";
    }
  }

  List< std::pair< int, List< int > > > listSumAndNums;
  int nowSize = 0;
  while (true)
  {
    List< int > nums;
    int sum = 0;

    for (auto element = list.begin(); element != list.end(); ++element)
    {
      List< int > nowList = element->second;
      int index = 0;

      for (auto numList = (element->second).begin(); numList != (element->second).end(); ++numList)
      {
        if (index == nowSize)
        {
          sum += *numList;
          nums.push_back(*numList);
          break;
        }
        index++;
      }
    }

    if (!nums.empty())
    {
      listSumAndNums.push_back({sum, nums});
    }
    else
    {
      break;
    }

    nowSize++;
  }

  if (listSumAndNums.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  std::cout << "\n";

  for (auto element = listSumAndNums.begin(); element != listSumAndNums.end(); ++element)
  {
    for (auto num = (element->second).begin(); num != (element->second).end(); ++num)
    {
      std::cout << *num;
      auto next = num;
      if (next.get_BiList()->next_ != nullptr)
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  for (auto element = listSumAndNums.begin(); element != listSumAndNums.end(); ++element)
  {
    std::cout << element->first;
    auto next = element;
    if (++next != listSumAndNums.end())
    {
      std::cout << " ";
    }
  }

  std::cout << "\n";
  return 0;
}
