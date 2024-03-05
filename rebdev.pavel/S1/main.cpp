#include <iostream>
#include <utility>
#include <string>
#include <limits>

#include "biList.hpp"
#include "pairsFunction.hpp"

int main()
{
  using list = rebdev::BiList< size_t >;
  using pairs = std::pair< std::string, list>;
  pairs * pairArr = nullptr;
  list * numList = nullptr;
  std::string listName;
  size_t numOfPairs = 0;
  size_t maxNumber = 0;


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

  if (numOfPairs == 0)
  {
    std::cout << "0\n";
    return 0;
  }
  else if ((numOfPairs == 1) && (!pairArr[0].second.capacity()))
  {
    std::cout << pairArr[0].first << "0\n";
    return 0;
  }

  for (size_t i = 0; i < (numOfPairs - 1); ++i)
  {
    std::cout << pairArr[i].first << ' ';
  }
  std::cout << pairArr[numOfPairs - 1].first << '\n';

  size_t sumOfNum[maxNumber] = {};
  bool overlowError = false;

  for (size_t i = 0; i < maxNumber; ++i)
  {
    bool firstElement = true;
    for (size_t j = 0; j < numOfPairs; ++j)
    {
      list & numList = pairArr[j].second;
      if (numList.capacity())
      {
        size_t element = numList.front();
        if (!firstElement)
        {
          std::cout << ' ';
        }
        std::cout << element;

        if ((std::numeric_limits< size_t >::max() - sumOfNum[j]) >= element)
        {
          sumOfNum[i] += element;
        }
        else
        {
          overlowError = true;
        }

        numList.pop_front();
        firstElement = false;
      }
    }
    std::cout << '\n';
  }

  delete[] pairArr;

  if (overlowError)
  {
    std::cerr << "overlow in math operation\n";
    return 1;
  }

  for (size_t i = 0; i < (maxNumber - 1); ++i)
  {
    std::cout << sumOfNum[i] << ' ';
  }

  std::cout << sumOfNum[maxNumber - 1] << '\n';

  return 0;
}
