#ifndef READINPUT_HPP
#define READINPUT_HPP

#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< size_t > > >& sequences, std::istream& input);
}

#endif
