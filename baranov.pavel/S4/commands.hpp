#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include <tree/tree.hpp>

namespace baranov
{
  using basicTree = Tree< int, std::string >;
  using treeOfTrees = Tree< std::string, basicTree >;
  void print(const treeOfTrees & trees, std::istream & in, std::ostream & out);
  void complement(treeOfTrees & trees, std::istream & in, std::ostream &);
  void intersect(treeOfTrees & trees, std::istream & in, std::ostream &);
  void unite(treeOfTrees & trees, std::istream & in, std::ostream &);
}

#endif

