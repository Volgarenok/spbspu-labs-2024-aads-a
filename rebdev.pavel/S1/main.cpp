#include <iostream>
#include <utility>
#include <string>

#include "biList.hpp"
#include "pairsFunction.hpp"

int main()
{
  using list = rebdev::BiList< size_t >;
  using pairs = std::pair< std::string, list>;
  pairs * pairArr = nullptr;
  size_t numOfPairs = 0;
  size_t maxNumber = 0;
  list * numList = nullptr;
  std::string listName;

  while (std::cin >> listName)
  {
    try
    {
      numList = new list;

      maxNumber = std::max(maxNumber, rebdev::inputNumbersList(std::cin, numList));

      pairArr = rebdev::expandPairArr(pairArr, numOfPairs);
      pairArr[numOfPairs].first = listName;
      pairArr[numOfPairs].second = *numList;
      numOfPairs += 1;

      delete numList;
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
  std::cout << '\b' << '\n';

  size_t sumOfNum[maxNumber] = {};
  for (size_t i = 0; i < maxNumber; ++i)
  {
    for (size_t j = 0; j < numOfPairs; ++j)
    {
      list & numList = pairArr[j].second;
      if (numList.capacity())
      {
        size_t element = numList.front();
        std::cout << element << ' ';
        sumOfNum[i] += element;
        numList.pop_front();
      }
    }
    std::cout << '\b' << '\n';
  }
  for (size_t i = 0; i < maxNumber; ++i)
  {
    std::cout << sumOfNum[i] << ' ';
  }
  std::cout << '\b' << '\n';

  delete[] pairArr;
  return 0;
}
