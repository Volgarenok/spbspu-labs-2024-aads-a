#ifndef INPUTMAP_HPP
#define INPUTMAP_HPP
#include <iosfwd>
#include <map>
#include <string>
#include "binarySearchTree.hpp"

namespace strelyaev
{
  void inputMap(std::istream&, Tree< std::string, Tree< int, std::string > >&);
}

#endif

