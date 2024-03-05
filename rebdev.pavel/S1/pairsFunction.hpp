#ifndef PAIRSFUNCTION
#define PAIRSFUNCTION

#include <iostream>
#include <utility>
#include <string>

#include "biList.hpp"

namespace rebdev
{
  using pairs = std::pair< std::string, rebdev::BiList< size_t >>;

  pairs * expandPairArr(pairs * pairsArr, size_t numOfPairs);
  size_t inputNumbersList(std::istream & in, BiList< size_t >* numList);
}

#endif
