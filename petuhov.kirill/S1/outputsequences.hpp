#ifndef OUTPUTSEQUENCES_HPP
#define OUTPUTSEQUENCES_HPP

#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > >& sequences, List< unsigned long long >& sums);
}

#endif

