#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <AVLtree.hpp>

namespace novokhatskiy
{
  using mainMap = Tree< std::string, Tree< size_t, std::string > >;
  using map = Tree< size_t, std::string >;
  void print(const mainMap &dict, std::istream &in, std::ostream &out);
  void complement(mainMap &dict, std::istream &in);
  void intersectCmd(mainMap &dict, std::istream &in);
  void unionCmd(mainMap &dict, std::istream &in);
}

#endif
