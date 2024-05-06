#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <map>
#include <string>

namespace strelyaev
{
  void print(std::istream&, std::map< std::string, std::map< int, std::string > >&, std::ostream&);
  void getComplement(std::istream&, std::map< std::string, std::map< int, std::string > >&);
  void getIntersect(std::istream&, std::map< std::string, std::map< int, std::string > >&);
  void getUnion(std::istream&, std::map< std::string, std::map< int, std::string > >&);
}

#endif
