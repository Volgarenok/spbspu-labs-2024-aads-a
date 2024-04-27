#ifndef DICTIONARY_COMMAND_HPP
#define DICTIONARY_COMMAND_HPP

#include <iosfwd>
#include <string>
#include "input_output_collection.hpp"

namespace erohin
{
  std::string * parseStringBySpace(std::string * dest, size_t size, const std::string & source);
  void print(const collection & context, std::istream & input, std::ostream & output);
  void complement(collection & context, std::istream & input, std::ostream &);
  void intersect(collection & context, std::istream & input, std::ostream &);
  void unite(collection & context, std::istream & input, std::ostream &);
}

#endif
