#ifndef LIST_FUNCTIONS_HPP
#define LIST_FUNCTIONS_HPP

#include <istream>
#include <utility>
#include "list.hpp"

namespace grechishnikov
{
  using namedList = std::pair < std::string, List< size_t > >;

  namedList inputList(std::istream& in);
  List< namedList > inputLists(std::istream& in);
  size_t countSum(const List< size_t >& list);
  void outputList(const List< size_t >& lisr, std::ostream& out);
}

#endif
