#ifndef INPUTMAP_HPP
#define INPUTMAP_HPP
#include <iosfwd>
#include <tree/binarySearchTree.hpp>

namespace strelyaev
{
  Tree< int, std::string > inputMap(std::istream&);
}

#endif
