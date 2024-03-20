#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include "list.hpp"

namespace piyavkin
{
  void inputList(std::istream& in, List< std::pair< std::string, List< unsigned long long > > >& list);
}
#endif
