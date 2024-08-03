#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iosfwd>
#include "tree.hpp"

namespace isaychev
{
  using dataset_t = isaychev::BSTree< int, std::string >;
  using map_t = BSTree< std::string, dataset_t >;
  using cstr_ref = const std::string &;

  void print(std::ostream & out, const std::string & name, const map_t & dicts);
  void complement(cstr_ref new_name, cstr_ref name1, cstr_ref name2, map_t & dicts);
}

#endif
