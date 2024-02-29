#include <iostream>
#include <utility>
#include <string>

#include "biList.hpp"
#include "pairsFunction.hpp"

int main()
{
  using pairs = std::pair < std::string, rebdev::BiList< size_t > >;
  pairs * pairsArr = nullptr;
  size_t numOfPairs = 0;
  size_t maxNumber = 0;

  while (!std::cout.eof())
  {
    std::string listName;
    rebdev::BiList < size_t > numList;

    try
    {
      rebdev::expandPairArr(pairsArr, numOfPairs);
      std::getline(std::cin, listName, ' ');
      size_t num = rebdev::inputNumbersList(std::cin, numList);
      maxNumber = std::max(maxNumber, num);
      pairsArr[numOfPairs++] = std::make_pair(listName, numList);
    }
    catch (const std::exception & e)
    {
      delete[] pairsArr;
      std::cerr << e.what();
      return 1;
    }
  }

  for (size_t i = 0; i < numOfPairs; ++i)
  {
    std::cout << std::get < 0 > (pairsArr[i]) << ' ';
  }
  std::cout << '\n';
  size_t sumOfNum[maxNumber] = {};
  for (size_t i = 0; i < maxNumber; ++i)
  {
    for (size_t j = 0; j < numOfPairs; ++i)
    {
      try
      {
        size_t element = std::get < 1 > (pairsArr[j]).front();
        std::cout << element << ' ';
        sumOfNum[i] += element;
        std::get< 1 >(pairsArr[j]).pop_front();
      }
      catch (...){}
    }
    std::cout << '\n';
  }
  for (size_t i = 0; i < maxNumber; ++i)
  {
    std::cout << sumOfNum[i] << ' ';
  }

  delete[] pairsArr;
  return 0;
}
