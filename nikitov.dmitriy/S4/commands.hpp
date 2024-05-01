#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include "tree.hpp"

namespace nikitov
{
  void printCmd(const Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input, std::ostream& output);

  void complementCmd(Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input);

  void intersectCmd(Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input);

  void unionCmd(Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input);
}
#endif
