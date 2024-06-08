#ifndef READ_SEQUENCES_HPP
#define READ_SEQUENCES_HPP

#include <iostream>

#include "list.hpp"

namespace belokurskaya
{
  void readSequences(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences);
  void readElem(List< List< size_t > >& outList, List< std::pair< std::string, List< size_t > > >& inList);
}

#endif
