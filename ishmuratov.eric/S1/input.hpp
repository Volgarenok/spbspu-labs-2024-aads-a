#ifndef INPUT_HPP
#define INPUT_HPP

#include <istream>
#include <string>
#include <bdlist.hpp>

namespace ishmuratov
{
  void inputList(List< std::pair< std::string, List< size_t > > > & pairs, std::istream & input);
}

#endif
