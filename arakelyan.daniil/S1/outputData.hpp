#ifndef OUTPUTPROC_HPP
#define OUTPUTPROC_HPP

#include <iostream>
#include "binList.hpp"

namespace arakelyan
{

  using BinList_t = arakelyan::BinList< std::pair< std::string, arakelyan::BinList< size_t > > >;
  void outputPairsNames(BinList_t listOfPairs, std::ostream &out);
  void outputPairsLists(BinList_t &listOfPairs, arakelyan::BinList< size_t > &sumList, std::ostream &out);
  void outputPairListsSums(arakelyan::BinList< size_t > sumList, std::ostream &out);
}

#endif
