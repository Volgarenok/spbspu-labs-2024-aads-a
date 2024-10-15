#ifndef INPUT_FUNC_HPP 
#define INPUT_FUNC_HPP 

#include <string>
#include <istream>
#include <utility>
#include "forwardlist.hpp"

namespace agarkov
{
  std::pair< std::string, ForwardList< size_t > > inputList(std::istream &in);
  ForwardList< std::pair < std::string, ForwardList< size_t > > > inputLists(std::istream& in);
}

#endif
