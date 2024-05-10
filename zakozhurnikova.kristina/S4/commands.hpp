#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <list.hpp>
#include <string>
#include "binarySearchTree.hpp"

namespace zakozhurnikova
{
  using map = BinarySearchTree< int, std::string >;
  using tree = BinarySearchTree< std::string, map >;
  void print(List< std::string >& args, std::string& result, tree& maps_);
  void complement(List< std::string >& args, std::string& result, tree& maps_);
  void intersect(List< std::string >& args, std::string& result, tree& maps_);
  void doUnion(List< std::string >& args, std::string& result, tree& maps_);
}

#endif
