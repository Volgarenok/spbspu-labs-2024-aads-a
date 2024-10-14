#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <string>
#include <ostream>
#include <tree.hpp>
#include "key_sum.hpp"

namespace sakovskaia
{
  void input(Tree< int, std::string > & dictionary, std::istream & input);
  void ascending(const Tree< int, std::string > & tree, KeySum & f, std::ostream & output);
  void breadth(const Tree< int, std::string > & tree, KeySum & f, std::ostream & output);
  void descending(const Tree< int, std::string > & tree, KeySum & f, std::ostream & output);
}

#endif
