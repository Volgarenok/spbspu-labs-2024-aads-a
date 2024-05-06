#ifndef INPUTMAP_HPP
#define INPUTMAP_HPP
#include <iosfwd>
#include <map>
#include <string>

namespace strelyaev
{
  void inputMap(std::istream&, std::map< std::string, std::map< int, std::string > >&);
}

#endif