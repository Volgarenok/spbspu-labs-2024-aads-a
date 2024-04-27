#ifndef INPUT_OUTPUT_COLLECTION_HPP
#define INPUT_OUTPUT_COLLECTION_HPP

#include <map>
#include <string>
#include <iosfwd>

namespace erohin
{
  using dictionary = std::map< size_t, std::string >;
  using collection = std::map< std::string, dictionary >;

  void inputCollection(std::istream & input, collection & dest);
  void outputCollection(std::ostream & output, const collection & source);
}

#endif
