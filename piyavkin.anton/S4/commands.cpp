#include "commands.hpp"
#include <iostream>

void piyavkin::print(std::ostream& out, const std::string& str, const map_t& map)
{
  const tree_t res = map.at(str);
  out << str;
  for (auto it = res.cbegin(); it != res.cend(); ++it)
  {
    out << ' ' << it->first << ' ' << it->second;
  }
}