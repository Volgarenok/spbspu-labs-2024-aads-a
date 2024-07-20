#ifndef IO_DATASTRUCT_HPP
#define IO_DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <utility>
#include <list.hpp>

namespace lebedev
{
  using listOfPairs = List< std::pair< std::string, List< size_t > > >;
  size_t inputDS(std::istream & input, listOfPairs & pairs);
  void countSums(listOfPairs & pairs, List< size_t > & sums, size_t max_pair_size);
  void outputPairsNames(std::ostream & output, listOfPairs & pairs);
  void outputSequences(std::ostream & output, listOfPairs & pairs, size_t max_pair_size);
  void outputSums(std::ostream & output, List< size_t > sums);
}

#endif
