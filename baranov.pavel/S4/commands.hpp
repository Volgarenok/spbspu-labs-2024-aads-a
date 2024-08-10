#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include "tree.hpp"

namespace baranov
{
  using basicTree = Tree< int, std::string >;
  using treeOfTrees = Tree< std::string, basicTree >;
  void print(const treeOfTrees & trees, std::istream & in, std::ostream & out);
}

#endif

