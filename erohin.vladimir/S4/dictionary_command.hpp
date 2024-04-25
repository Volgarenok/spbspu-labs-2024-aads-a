#ifndef DICTIONARY_COMMAND_HPP
#define DICTIONARY_COMMAND_HPP

#include <map>
#include <iosfwd>

namespace erohin
{
  using dict = std::map< size_t, std::string >;

  void print(std::ostream & output, const dict & dest);
  void implement(std::istream & input, std::ostream & output, dict & dest, const dict & source1, const dict & source2);
  void intersect(std::istream & input, std::ostream & output, dict & dest, const dict & source1, const dict & source2);
  void unite(std::istream & input, std::ostream & output, dict & dest, const dict & source1, const dict & source2);
}

#endif
