#include <iostream>
#include <limits>
#include <string>
#include <cstddef>
#include "list.hpp"
#include "inputOutputList.hpp"

int main()
{
  using namespace chistyakov;
  List< std::pair< std::string, List< size_t > > > list;

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

  outputNames(list);
  size_t max_digit = maxDigit(list);
  std::cout << "\n";

  List< std::pair< size_t, List< size_t > > > listSumAndNums;
  size_t nowSize = 0;
  size_t max_size = std::numeric_limits< size_t >::max();
  bool overflow = false;

  for (size_t i = 0; i < max_digit; ++i)
  {
    List< size_t > nums;
    size_t sum = 0;

    for (auto element = list.begin(); element != list.end(); ++element)
    {
      size_t index = 0;

      for (auto numList = (element->second).begin(); numList != (element->second).end(); ++numList)
      {
        if (index == nowSize)
        {
          if (sum < max_size - *numList)
          {
            sum += *numList;
          }
          else
          {
            overflow = true;
            sum = *numList;
          }
          nums.push_back(*numList);
        }
        index++;
      }
    }

    if (!nums.empty())
    {
      listSumAndNums.push_back(std::pair< size_t, List < size_t > >(sum, nums));
    }
    else
    {
      break;
    }

    nowSize++;
  }

  outputNums(listSumAndNums);
  if (listSumAndNums.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  if (overflow)
  {
    std::cerr << "Overflow\n";
    return 1;
  }

  outputSums(listSumAndNums);

  std::cout << "\n";
  return 0;
}
