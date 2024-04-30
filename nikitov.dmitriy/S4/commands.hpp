#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <map>

namespace nikitov
{
  void printCmd(const std::map< std::string, std::map< size_t, std::string > >&, std::istream&, std::ostream&);

  void complementCmd(const std::map< std::string, std::map< size_t, std::string > >&, std::istream&, std::ostream&);

  void intersectCmd(const std::map< std::string, std::map< size_t, std::string > >&, std::istream&, std::ostream&);

  void unionCmd(const std::map< std::string, std::map< size_t, std::string > >&, std::istream&, std::ostream&);
}
#endif