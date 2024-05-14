#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <string>
#include <binarySearchTree.hpp>
#include <list.hpp>

namespace zakozhurnikova
{
  using map = BinarySearchTree< int, std::string >;
  using tree = BinarySearchTree< std::string, map >;
  void print(const List< std::string >& args, std::string& result, const tree& maps);
  void complement(List< std::string >& args, std::string& result, tree& maps);
  void intersect(List< std::string >& args, std::string& result, tree& maps);
  void doUnion(List< std::string >& args, std::string& result, tree& maps);
}

#endif
