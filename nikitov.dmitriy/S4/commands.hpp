#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <map>

namespace nikitov
{
  void printCmd(const std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input, std::ostream& output);

  void complementCmd(std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input);

  void intersectCmd(std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input);

  void unionCmd( std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input);
}
#endif