#include <iostream>
#include <utility>
#include <string>

#include "biList.hpp"
#include "pairsFunction.hpp"

int main()
{
  using pairs = std::pair< std::string, rebdev::BiList< size_t >>;
  pairs * pairArr = nullptr;
  size_t numOfPairs = 0;
  size_t maxNumber = 0;
  rebdev::BiList< size_t >* numList = nullptr;
  std::string listName;

  while (std::getline(std::cin, listName, ' '))
  {
    try
    {
      numList = new rebdev::BiList< size_t >;

      maxNumber = std::max(maxNumber, rebdev::inputNumbersList(std::cin, numList));

      pairArr = rebdev::expandPairArr(pairArr, numOfPairs);
      pairArr[numOfPairs].first = listName;
      pairArr[numOfPairs].second = *numList;
      numOfPairs += 1;
    }
    catch (const std::exception & e)
    {
      delete[] pairArr;
      std::cerr << e.what();
      return 1;
    }

    listName.clear();
  }

  for (size_t i = 0; i < numOfPairs; ++i)
  {
    std::cout << pairArr[i].first << ' ';
  }
  std::cout << '\n';

  size_t sumOfNum[maxNumber] = {};
  for (size_t i = 0; i < maxNumber; ++i)
  {
    for (size_t j = 0; j < numOfPairs; ++j)
    {
      try
      {
        size_t element = pairArr[j].second.front();
        std::cout << element << ' ';
        sumOfNum[i] += element;
        pairArr[j].second.pop_front();
      }
      catch (...){}
    }
    std::cout << '\n';
  }
  for (size_t i = 0; i < maxNumber; ++i)
  {
    std::cout << sumOfNum[i] << ' ';
  }

  delete[] pairArr;
  return 0;
}
