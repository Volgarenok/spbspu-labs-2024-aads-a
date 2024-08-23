#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP
#include "forwardList.hpp"
#include <istream>
#include <cstddef>

namespace chernov
{
  using namedNumberedList = std::pair< std::string, List< size_t > >;
  void inputLists(std::istream& input, List< namedNumberedList >& list);
}

#endif
