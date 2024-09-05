#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

#include <iostream>
#include <cstddef>
#include <list.hpp>

namespace skuratov
{
  void inputAll(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences);
  void outputAll(const List< std::pair< std::string, List< size_t > > > & sequences, std::ostream& out);
}
#endif
