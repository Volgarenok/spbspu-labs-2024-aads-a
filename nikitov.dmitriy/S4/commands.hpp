#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include "tree.hpp"

namespace nikitov
{
  void printCmd(const Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input, std::ostream& output);

  void inputCmd(Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input, const std::string& cmd);
}
#endif
