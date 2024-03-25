#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iostream>
#include "binList.hpp"
#include "binList.cpp"

namespace arakelyan
{
  void inputData(std::istream& in, BinList < std::pair < std::string, BinList< size_t > > > &listOfLists);
}

#endif
