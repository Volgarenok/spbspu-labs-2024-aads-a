#include <iostream>
#include <exception>
#include <limits>
#include <string>
#include <stdexcept>

#include "binList.hpp"
#include "inputData.hpp"
#include "iterator.hpp"
#include "node.hpp"

int main()
{
  using namespace arakelyan;

  BinList< std::pair< std::string, BinList < size_t > > > listOfPairs;

  try
  {
    inputData(std::cin, listOfPairs);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }

  if (listOfPairs.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
  {
    std::cout << iter->first << " ";
  }
  std::cout << "\n";

  size_t maxSize = std::numeric_limits< size_t >::max();
  BinList< int > sumList;


  bool overflow = false;

  for (size_t i = 0; i < listOfPairs.getSize(); ++i)
  {
    size_t sum = 0;
    for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
    {
      if (!iter->second.isEmpty())
      {
        std::cout << iter->second.getFirst() << " ";
        if (sum < (maxSize - iter->second.isEmpty()))
        {
          sum += iter->second.getFirst();
        }
        else
        {
          overflow = true;
        }
        iter->second.pop_front();
      }
    }
    sumList.push_back(sum);
    std::cout << "\n";
  }
  if (overflow)
  {
    std::cerr << "overflow error\n";
    return 1;
  }
  for (auto it = sumList.begin(); it != sumList.end(); ++it)
  {
    std::cout << *it << " ";
  }

  return 0;
}

