#ifndef INPUTMAPS_HPP
#define INPUTMAPS_HPP

#include <iosfwd>

#include <binarySearchTree.hpp>

namespace marishin
{
  void inputMaps(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& maps);
}

#endif
