#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <tree.hpp>
#include "keysum.hpp"

namespace piyavkin
{
  void traverse_ascending(std::ostream& out, const Tree< int, std::string >& tree, KeySum& f);
  void traverse_descending(std::ostream& out, const Tree< int, std::string >& tree, KeySum& f);
  void traverse_breadth(std::ostream& out, const Tree< int, std::string >& tree, KeySum& f);
}
#endif
