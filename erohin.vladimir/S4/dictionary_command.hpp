#ifndef DICTIONARY_COMMAND_HPP
#define DICTIONARY_COMMAND_HPP

#include <map>
#include <iosfwd>
#include <string>

namespace erohin
{
  using dictionary = std::map< size_t, std::string >;
  using collection = std::map< std::string, dictionary >;

  void print(const collection & context, std::istream & input, std::ostream & output);
  void implement(collection & context, std::istream & input, std::ostream &);
  void intersect(collection & context, std::istream & input, std::ostream &);
  void unite(collection & context, std::istream & input, std::ostream &);
}

#endif
