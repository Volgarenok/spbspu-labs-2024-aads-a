#ifndef COMLINEARG_HPP
#define COMLINEARG_HPP
#include <ostream>
#include <tree.hpp>

namespace piyavkin
{
  using tree_t = Tree< std::string, size_t >;
  using dic_t = Tree< std::string, tree_t >;
  void help(std::ostream& out);
  void check(std::istream& in, std::ostream& out, dic_t& dicts);
}
#endif

