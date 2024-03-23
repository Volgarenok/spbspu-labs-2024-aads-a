#include <iostream>
#include <climits>
#include <string>
#include "list.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"
#include "inputOutputList.hpp"

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
    return 1;
  }

  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  outPutNames(list);
  int max_digit = maxDigit(list);

  std::cout << "\n";

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
        max_digit = std::max(max_digit, *numList);
        if (index == nowSize)
        {
          if (sum < INT_MAX - *numList)
          {
            sum += *numList;
            nums.push_back(*numList);
            break;
          }
          else
          {
            std::cerr << "Overflow\n";
            return 1;
          }
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

  outPutNums(listSumAndNums);

  if (listSumAndNums.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  outPutSums(listSumAndNums);

  std::cout << "\n";
  return 0;
}
