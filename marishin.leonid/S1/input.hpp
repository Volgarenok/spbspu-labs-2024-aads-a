#ifndef INPUT_HPP
#define INPUT_HPP

#include <istream>
#include <string>
#include <linkedList.hpp>

namespace marishin
{
  void inputList(LinkedList< std::pair< std::string, LinkedList< size_t > > > & pairs, std::istream & input);
}

#endif
