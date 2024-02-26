#ifndef PAIRSFUNCTION
#define PAIRSFUNCTION

#include <iostream>
#include <utility>
#include <string>

#include "biList.hpp"

namespace rebdev
{
  void expandPairArr(std::pair < std::string, BiList < size_t > > * pairsArr, size_t numOfPairs);
  size_t inputNumbersList(std::istream & in, BiList < size_t > & numList);
}

#endif
