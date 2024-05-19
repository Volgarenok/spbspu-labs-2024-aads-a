#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <string>
#include <iostream>
#include <treeNode.hpp>


namespace marishin
{
  using tree = BinarySearchTree< std::string, BinarySearchTree< int, std::string > >;
  void print(std::istream& in, const tree& myMap, std::ostream& out);
  void doUnion(std::istream& in, tree& myMap);
  void doComplement(std::istream& in, tree& myMap);
  void doIntersect(std::istream& in, tree& myMap);
}

#endif
