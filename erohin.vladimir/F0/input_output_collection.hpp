#ifndef INPUT_OUTPUT_COLLECTION_HPP
#define INPUT_OUTPUT_COLLECTION_HPP

#include <string>
#include <iosfwd>
#include "red_black_tree.hpp"
#include "dictionary.hpp"

namespace erohin
{
  using collection = RedBlackTree< std::string, Dictionary >;

  void inputCollection(collection & dict_context, std::istream & input);
  void outputCollection(const collection & dict_context, std::ostream & output);
}

#endif
