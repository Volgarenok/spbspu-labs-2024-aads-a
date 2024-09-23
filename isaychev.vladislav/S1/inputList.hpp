#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP

#include <string>
#include <iosfwd>
#include <list/list.hpp>

namespace isaychev
{
  using ullList = List< unsigned long long int >;
  void inputList(std::istream & in, List< std::pair< std::string, ullList > > & list);
}

#endif
