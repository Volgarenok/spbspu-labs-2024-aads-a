#ifndef READINPUT_HPP
#define READINPY_HPP

#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< int > > > &sequence, std::istream &input);
}

#endif
