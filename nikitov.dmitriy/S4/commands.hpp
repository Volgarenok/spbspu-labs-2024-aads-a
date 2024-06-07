#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <tree.hpp>

namespace nikitov
{
  void printCmd(const Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& dictName, std::ostream& output);

  void complementCmd(Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& newDictName,
    const std::string& firstDictName, const std::string& secondDictName);

  void intersectCmd(Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& newDictName,
    const std::string& firstDictName, const std::string& secondDictName);

  void unionCmd(Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& newDictName,
    const std::string& firstDictName, const std::string& secondDictName);
}
#endif
