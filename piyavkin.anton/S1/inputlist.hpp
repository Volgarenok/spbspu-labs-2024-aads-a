#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP
#include <istream>
#include "list.hpp"

namespace piyavkin
{
  using pair_t = std::pair< std::string, piyavkin::List< unsigned long long >* >*;
  pair_t inputList(std::istream& in, size_t& size, size_t& max_size_list);
}
#endif
