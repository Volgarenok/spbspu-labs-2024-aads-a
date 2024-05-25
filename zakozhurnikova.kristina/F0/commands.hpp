#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <list.hpp>
#include <binarySearchTree.hpp>
#include <string>
#include <utility>

namespace zakozhurnikova
{
  using dict = BinarySearchTree< std::string, BinarySearchTree< std::string, List< std::string > > >;
  void print(const List< std::string >& args, std::string& result, const dict& dictionary);
}

#endif
