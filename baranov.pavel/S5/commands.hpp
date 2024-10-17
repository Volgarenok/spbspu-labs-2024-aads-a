#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <ostream>
#include <tree/tree.hpp>

namespace baranov
{
  void ascending(std::ostream & out, const Tree< int, std::string > & tree);
  void descending(std::ostream & out, const Tree< int, std::string > & tree);
  void breadth(std::ostream & out, const Tree< int, std::string > & tree);
}

#endif

