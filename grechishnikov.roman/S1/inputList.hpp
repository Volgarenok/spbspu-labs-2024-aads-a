#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <utility>
#include "list.hpp"

namespace grechishnikov
{
  using namedList = std::pair < std::string, List< size_t > >;
  namedList inputList(std::istream& in);
  List< namedList > inputLists(std::istream& in);
}

#endif
