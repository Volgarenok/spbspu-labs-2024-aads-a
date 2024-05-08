#ifndef INPUTMAPS_HPP
#define INPUTMAPS_HPP
#include <iosfwd>
#include <binarySearchTree.hpp>
#include <scopeGuard.hpp>

namespace zakozhurnikova
{
  void inputMap(std::istream& in, BinarySearchTree< long long, std::string >& map);
}

#endif
