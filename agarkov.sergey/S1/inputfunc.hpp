#ifndef INPUT_FUNC_HPP
#define INPUT_FUNC_HPP

#include <string>
#include <istream>
#include <utility>
#include "forwardlist.hpp"

namespace agarkov
{
  using pair_t = std::pair< std::string, ForwardList< size_t > >;
  pair_t inputList(std::istream &in);
  ForwardList< pair_t > inputLists(std::istream& in);
}

#endif
