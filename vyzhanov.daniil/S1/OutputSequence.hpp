#ifndef OUTPUTSEQUENCE_HPP
#define OUTPUTSEQUENCE_HPP

#include <iosfwd>
#include <limits>
#include "List.hpp"

namespace vyzhanov
{
  using pair = std::pair< std::string, List< size_t > >;
  std::ostream& outputList(std::ostream& os, const List< size_t >& list);
  size_t maxListSize(const List< pair >&);
  void outputNames(const List< pair >&, std::ostream&);
  void outputNums(List< pair >&, std::ostream&);
  void printSums(const List< pair >&, std::ostream&);
}

#endif
