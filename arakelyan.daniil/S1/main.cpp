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
        if (sum < maxSize - iter->second.isEmpty())
        {
          std::cout << iter->second.getFirst() << " ";
          iter->second.pop_front();
        }
        else
        {
          overflow = true;
        }
      }
    }
    std::cout << "\n";
  }


  return 0;
}

