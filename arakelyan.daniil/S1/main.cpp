#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>

#include <list/binList.hpp>
#include <list/iterator.hpp>
#include "inputData.hpp"
#include "outputData.hpp"

int main()
{
  using namespace arakelyan;

  BinList< std::pair< std::string, BinList < size_t > > > listOfPairs;

  try
  {
    inputData(std::cin, listOfPairs);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (listOfPairs.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  BinList< size_t > sumList;

  try
  {
    outputPairsNames(std::cout, listOfPairs);
    outputPairsLists(std::cout, listOfPairs, sumList);
    outputPairListsSums(std::cout, sumList);
    std::cout << "\n";
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}

