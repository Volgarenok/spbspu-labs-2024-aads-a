#ifndef IO_DATASTRUCT_HPP
#define IO_DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <utility>
#include "list.hpp"

namespace lebedev
{
  using listOfPairs = List< std::pair< std::string, List< size_t > > >;
  void inputDS(std::istream & input, listOfPairs & pairs);
  void outputPairsNames(std::ostream & output, listOfPairs & pairs);;
}

#endif
