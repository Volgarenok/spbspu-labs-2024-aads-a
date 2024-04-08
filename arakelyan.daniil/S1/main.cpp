#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>

#include "inputData.hpp"
#include <binList.hpp>
#include "outputData.hpp"
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
    outputPairsNames(listOfPairs, std::cout);
    outputPairsLists(listOfPairs, sumList, std::cout);
    outputPairListsSums(sumList, std::cout);
    std::cout << "\n";
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}

