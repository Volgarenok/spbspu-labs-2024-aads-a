#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <ostream>
#include <cstddef>
#include "list.hpp"

namespace piyavkin
{
  using pair_t = std::pair< std::string, piyavkin::List< unsigned long long >* >*;
  void output(std::ostream& out, const pair_t pairs, size_t size, size_t max_size_list);
}
#endif
