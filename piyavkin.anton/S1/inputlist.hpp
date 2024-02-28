#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include "list.hpp"

namespace piyavkin
{
  using pair_t = std::pair< std::string, piyavkin::List< unsigned long long >* >*;
  void freeMemory(pair_t pairs, size_t size);
  pair_t resize(pair_t old_pairs, size_t capacity);
  pair_t inputList(std::istream& in, size_t& size, size_t& max_size_list);
}
#endif
