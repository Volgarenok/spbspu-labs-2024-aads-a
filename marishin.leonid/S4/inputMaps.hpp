#ifndef INPUT_MAPS_HPP
#define INPUT_MAPS_HPP

#include <string>
#include <iostream>
#include <binarySearchTree.hpp>

namespace marishin
{
  Tree< std::string, Tree< size_t, std::string > > inputMaps(std::istream & in);
}

#endif
