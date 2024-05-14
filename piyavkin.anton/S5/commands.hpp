#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <tree.hpp>

namespace piyavkin
{
  void traverse_ascending(std::ostream& out, Tree< int, std::string > tree);
  void traverse_descending(std::ostream& out, Tree< int, std::string > tree);
  void traverse_breadth(std::ostream& out, Tree< int, std::string > tree);
}
#endif