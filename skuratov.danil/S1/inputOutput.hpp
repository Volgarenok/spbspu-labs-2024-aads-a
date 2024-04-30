#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

#include <iostream>
#include <cstddef>
#include "list.hpp"

namespace skuratov
{
  void inputAll(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences);
/*
  void outputNames(const List< std::pair< std::string, List< size_t > > >& sequences, std::ostream& out);
  void outputNumbers(const List< std::pair< std::string, List< size_t > > >& sequences, List< size_t >& numbers);
  void outputSums(const List< size_t >& numbers, std::ostream& out);
*/
}
#endif
