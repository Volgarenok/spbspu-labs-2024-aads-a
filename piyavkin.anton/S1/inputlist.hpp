#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include "list.hpp"

namespace piyavkin
{
  std::pair< std::string, List< unsigned int > >* inputList(std::istream& in);
}
#endif
