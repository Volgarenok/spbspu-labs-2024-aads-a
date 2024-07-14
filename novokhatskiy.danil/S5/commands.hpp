#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <string>
#include <AVLtree.hpp>

namespace novokhatskiy
{
  void ascending(int& num, std::string& str, Tree< int, std::string >& map);
  void descending(int& num, std::string& str, Tree< int, std::string >& map);
  void breadth(int& num, std::string& str, Tree< int, std::string >& map);
}

#endif
