#ifndef INPUT_DICTS_HPP
#define INPUT_DICTS_HPP

#include <string>
#include <map>
#include <iostream>
#include <binarySearchTree.hpp>

namespace marishin
{
  void inputMaps(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap);
}

#endif
