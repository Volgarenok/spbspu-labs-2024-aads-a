#ifndef INPUT_DICT_HPP
#define INPUT_DICT_HPP

#include <istream>
#include "tree.hpp"

namespace namestnikov
{
  void inputDict(std::istream & in, Tree< int, std::string > & myMap);
}

#endif
