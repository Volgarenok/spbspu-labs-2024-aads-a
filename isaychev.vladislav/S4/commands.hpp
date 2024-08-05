#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iosfwd>
#include <tree/tree.hpp>

namespace isaychev
{
  using dataset_t = isaychev::BSTree< int, std::string >;
  using map_t = BSTree< std::string, dataset_t >;

  void print(const map_t & dicts, std::ostream & out, std::istream & in);
  void complement(map_t & dicts, std::istream & in);
  void intersect(map_t & dicts, std::istream & in);
  void unite(map_t & dicts, std::istream & in);
}

#endif
