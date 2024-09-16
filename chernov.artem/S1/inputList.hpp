#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <cstddef>
#include "forwardList.hpp"

namespace chernov
{
  using namedNumberedList = std::pair< std::string, List< size_t > >;
  void inputLists(std::istream& input, List< namedNumberedList >& list);
}

#endif
