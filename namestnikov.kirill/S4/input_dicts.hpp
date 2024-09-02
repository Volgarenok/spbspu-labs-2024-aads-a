#ifndef INPUT_DICTS_HPP
#define INPUT_DICTS_HPP

#include <string>
#include <iostream>
#include <tree.hpp>

namespace namestnikov
{
  void inputMaps(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap);
}

#endif
