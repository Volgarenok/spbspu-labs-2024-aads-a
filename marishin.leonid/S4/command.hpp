#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <string>
#include <iostream>
#include <binarySearchTree.hpp>

namespace marishin
{
  void print(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< size_t, std::string > >& myMap, std::ostream& out);
  void doUnion(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< size_t, std::string > >& myMap);
  void doComplement(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< size_t, std::string > >& myMap);
  void doIntersect(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< size_t, std::string > >& myMap);
}

#endif
