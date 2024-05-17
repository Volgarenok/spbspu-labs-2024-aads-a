#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <string>
#include <binarySearchTree.hpp>
#include <list.hpp>
#include <utility>

namespace zakozhurnikova
{
  using map = BinarySearchTree< int, std::string >;

  int ascending(std::string& result, map& tree);
  int descending(std::string& result, map& tree);
  int breadth(std::string& result, map& tree);
}

#endif
