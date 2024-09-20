#ifndef DICT_FUNCTIONS
#define DICT_FUNCTIONS
#include <iostream>
#include <tree/tree.hpp>
#include <string>

namespace baranov
{
  using dict_t = Tree< std::string, size_t >;
  using pair_t = std::pair< std::string, size_t >;
  void extendDict(dict_t & dict, std::istream & in);
  void printElement(const pair_t & item, std::ostream & out);
  size_t getWordCount(const dict_t & dict, const std::string & word);
  bool countComparator(const pair_t & lhs, const pair_t & rhs);
}

#endif

