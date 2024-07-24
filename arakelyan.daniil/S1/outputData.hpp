#ifndef OUTPUTPROC_HPP
#define OUTPUTPROC_HPP

#include <iostream>
#include <list/binList.hpp>

namespace arakelyan
{
  using BinList_t = BinList< std::pair< std::string, BinList< size_t > > >;
  void outputPairsNames(std::ostream &out, BinList_t listOfPairs);
  void outputPairsLists(std::ostream &out, BinList_t &listOfPairs, arakelyan::BinList< size_t > &sumList);
  void outputPairListsSums(std::ostream &out, BinList< size_t > sumList);
}

#endif
