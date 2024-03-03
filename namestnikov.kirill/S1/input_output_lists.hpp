#ifndef INPUT_OUTPUT_LISTS_HPP
#define INPUT_OUTPUT_LISTS_HPP

#include <iostream>
#include "forward_list.hpp"

namespace namestnikov
{
  using pair_t = std::pair<std::string, ForwardList<unsigned long long>>;
  void inputLists(std::istream & in, ForwardList<pair_t> & dataList);
  void outputLists(std::ostream & out, ForwardList<pair_t> & dataList);
}

#endif
