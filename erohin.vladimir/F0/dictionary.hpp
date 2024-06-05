#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iosfwd>
#include <string>
#include "red_black_tree.hpp"

namespace erohin
{
  struct Dictionary
  {
    RedBlackTree< std::string, size_t > records;
  };

  std::istream & operator>>(std::istream & input, Dictionary & dict);
  std::ostream & operator<<(std::ostream & output, const Dictionary & dict);
}

#endif
