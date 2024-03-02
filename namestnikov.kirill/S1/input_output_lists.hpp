#ifndef INPUT_OUTPUT_LISTS_HPP
#define INPUT_OUTPUT_LISTS_HPP

#include <iostream>
#include "forward_list.hpp"

namespace namestnikov
{
  using pair_t = std::pair<std::string, ForwardList<int>>;
  void inputLists(std::istream & in, pair_t * listsArray);
  void outputLists(std::ostream & out, pair_t * listsarray);
}

#endif
