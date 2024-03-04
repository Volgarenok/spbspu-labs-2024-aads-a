#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iostream>
#include <utility>

#include "binList.hpp"
#include "binList.cpp"

namespace arakelyan
{
  using pair_t = std::pair< std::string, BinList< int > * > *;
  pair_t inputData(std::istream &input, size_t &size);
}
#endif
