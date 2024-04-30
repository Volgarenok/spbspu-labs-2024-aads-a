#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <map>

namespace nikitov
{
  void printCmd(const std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input, std::ostream& output);

  void complementCmd(const std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input , std::ostream& output);

  void intersectCmd(const std::map< std::string, std::map< size_t, std::string > >& tree, std::istream&input, std::ostream& output);

  void unionCmd(const std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input, std::ostream& output);
}
#endif