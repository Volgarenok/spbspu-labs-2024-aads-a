#ifndef INPUTFILE_HPP
#define INPUTFILE_HPP
#include <istream>
#include <tree.hpp>

namespace piyavkin
{
  using tree_t = Tree< int, std::string >;
  using map_t = Tree< std::string, tree_t >;
  void inputFile(std::istream& in, map_t& map);
}
#endif
