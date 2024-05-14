#ifndef OUTPUTNAMES_HPP
#define OUTPUTNAMES_HPP

#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void outputNames(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > >& sequences);
}

#endif

