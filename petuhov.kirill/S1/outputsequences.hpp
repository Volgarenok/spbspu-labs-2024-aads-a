#ifndef OUTPUTSEQUENCES_HPP
#define OUTPUTSEQUENCES_HPP

#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& sequences, List< size_t >& sums);
}

#endif

