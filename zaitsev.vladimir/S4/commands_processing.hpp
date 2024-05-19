#ifndef COMMANDS_PROCESSING_HPP
#define COMMANDS_PROCESSING_HPP
#include <iostream>
#include <string>
#include "map.hpp"

namespace zaitsev
{
  using dictionary = zaitsev::Map<int, std::string>;
  using ds_it = zaitsev::Map<int, std::string>::const_iterator;
  using library = zaitsev::Map< std::string, dictionary>;

  void init_lib(int argc, char** argv, library& dest);
  void read_ds(std::istream& in, library& dest);
  void print_ds(std::istream& in, library& lib);
  void complement_ds(std::istream& in, library& lib);
  void intersect_ds(std::istream& in, library& lib);
  void union_ds(std::istream& in, library& lib);
}
#endif
