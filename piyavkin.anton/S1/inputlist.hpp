#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include "list.hpp"

namespace piyavkin
{
  using list_t = List< std::pair< std::string, List< unsigned long long > > >;
  void inputList(std::istream& in, list_t& list);
}
#endif
