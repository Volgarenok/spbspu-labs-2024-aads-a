#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>

#include "binarySearchTree.hpp"

namespace belokurskaya
{
  void ascending(int& num, std::string& str, BinarySearchTree< int, std::string >& tree);
  void descending(int& num, std::string& str, BinarySearchTree< int, std::string >& tree);
  void breadth(int& num, std::string& str, BinarySearchTree< int, std::string >& tree);
}

#endif
