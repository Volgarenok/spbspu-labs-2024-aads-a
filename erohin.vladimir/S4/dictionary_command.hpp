#ifndef DICTIONARY_COMMAND_HPP
#define DICTIONARY_COMMAND_HPP

#include <iosfwd>
#include <string>
#include "red_black_tree.hpp"
#include "input_output_collection.hpp"

namespace erohin
{
  using dict_func = std::function< void(std::istream &, std::ostream &) >;
  using commands_source = RedBlackTree< std::string, dict_func >;
  void print(const collection & context, std::istream & input, std::ostream & output);
  void complement(collection & context, std::istream & input, std::ostream &);
  void intersect(collection & context, std::istream & input, std::ostream &);
  void unite(collection & context, std::istream & input, std::ostream &);
}

#endif
