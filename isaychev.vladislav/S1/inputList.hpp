#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP

#include <string>
#include <iosfwd>
#include "list.hpp"

namespace isaychev
{
  void inputList(std::istream & in, List< std::pair< std::string, List< size_t > > > & list);
}

#endif
