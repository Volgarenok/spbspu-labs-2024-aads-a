#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>

#include "inputData.hpp"
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

  if (listOfPairs.isEmpty())
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
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  // // names
  // for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
  // {
  //   if (iter != listOfPairs.begin())
  //   {
  //     std::cout << " ";
  //   }
  //   std::cout << iter->first;
  // }
  //
  // if ((listOfPairs.getSize() != 1) && !(listOfPairs.begin()->second.isEmpty()))
  // {
  //   std::cout << "\n";
  // }
  //
  // size_t maxSize = std::numeric_limits< size_t >::max();
  // BinList< int > sumList;
  // bool overflow = false;
  //
  // //elements
  // for (size_t i = 0; i < listOfPairs.getSize(); ++i)
  // {
  //   size_t outed = 0;
  //   size_t sum = 0;
  //   for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
  //   {
  //     if (!iter->second.isEmpty())
  //     {
  //       if (outed == 0)
  //       {
  //         std::cout << "";
  //       }
  //       else {
  //         std::cout << " ";
  //       }
  //       std::cout << iter->second.getFirst();
  //       ++outed;
  //       if (sum < (maxSize - iter->second.isEmpty()))
  //       {
  //         sum += iter->second.getFirst();
  //       }
  //       else
  //       {
  //         overflow = true;
  //       }
  //       iter->second.pop_front();
  //     }
  //   }
  //   sumList.push_back(sum);
  //   std::cout << "\n";
  // }
  // if (overflow)
  // {
  //   std::cerr << "overflow error\n";
  //   return 1;
  // }
  //
  // //sums
  // for (auto it = sumList.begin(); it != sumList.end(); ++it)
  // {
  //   if (it != sumList.begin())
  //   {
  //     std::cout << " ";
  //   }
  //   std::cout << *it;
  // }
  // std::cout << "\n";

  return 0;
}

