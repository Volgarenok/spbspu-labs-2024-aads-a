#ifndef INPUT_OUTPUT_COLLECTION_HPP
#define INPUT_OUTPUT_COLLECTION_HPP

#include <string>
#include <iosfwd>
#include "red_black_tree.hpp"

namespace erohin
{
  using dictionary = RedBlackTree< size_t, std::string >;
  using collection = RedBlackTree< std::string, dictionary >;

  void inputCollection(std::istream & input, collection & dest);
  void outputCollection(std::ostream & output, const collection & source);
}

#endif
