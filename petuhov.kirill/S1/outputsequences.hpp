#ifndef OUTPUTSEQUENCES_HPP
#define OUTPUTSEQUENCES_HPP

#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequences, List< int >& sums);
}

#endif

