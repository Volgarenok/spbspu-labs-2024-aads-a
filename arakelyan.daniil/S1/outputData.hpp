#ifndef OUTPUTPROC_HPP
#define OUTPUTPROC_HPP

#include <iostream>
#include "binList.hpp"

namespace arakelyan
{
  void outputPairsNames(arakelyan::BinList< std::pair< std::string, arakelyan::BinList< size_t > > > listOfPairs, std::ostream &out);
  void outputPairsLists(arakelyan::BinList< std::pair< std::string, arakelyan::BinList< size_t > > > &listOfPairs, arakelyan::BinList< size_t > &sumList, std::ostream &out);
  void outputPairListsSums(arakelyan::BinList< size_t > sumList, std::ostream &out);
}

#endif
