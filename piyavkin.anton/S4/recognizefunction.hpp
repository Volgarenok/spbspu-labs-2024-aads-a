#ifndef RECOGNIZEFUNCTION_HPP
#define RECOGNIZEFUNCTION_HPP
#include <istream>

namespace piyavkin
{
  using tree_t = Tree< int, std::string >;
  using map_t = Tree< std::string, tree_t >;
  void recognizeFunction(std::istream& in, map_t& map);
}
#endif