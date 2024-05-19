#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <string>
#include <iostream>
#include <treeNode.hpp>


namespace marishin
{
  void print(std::istream& in, const BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& myMap, std::ostream& out);
  void doUnion(std::istream& in,& in, BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& myMap);
  void doComplement(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& myMap);
  void doIntersect(std::istream& in, BinarySearchTree< std::string, BinarySearchTree< int, std::string > >& myMap);
}

#endif
