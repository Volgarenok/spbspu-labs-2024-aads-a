#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <map>

namespace novokhatskiy
{
  using mainMap = std::map< std::string, std::map< size_t, std::string > >;
  using map = std::map< size_t, std::string >;
  void print(mainMap& dict, std::istream& in, std::ostream& out);
  void complement(mainMap& dict, std::istream& in, std::ostream&);
  void intersectCmd(mainMap& dict, std::istream& in, std::ostream&);
  void unionCmd(mainMap& dict, std::istream& in, std::ostream&);
}

#endif
