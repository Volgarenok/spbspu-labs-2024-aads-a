#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <list.hpp>
#include <string>
#include <binarySearchTree.hpp>
#include "implementedCommands.hpp"

namespace zakozhurnikova
{
  using map = BinarySearchTree< int, std::string >;

  int ascending(std::string& result, map& tree);
  int descending(std::string& result, map& tree);
  int breadth(std::string& result, map& tree);
}

#endif
