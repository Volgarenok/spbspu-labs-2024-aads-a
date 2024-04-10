#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <ostream>
#include <cstddef>
#include "list.hpp"

namespace piyavkin
{
  using list_t = List< std::pair< std::string, List< unsigned long long > > >;
  size_t max_size_list(const list_t& list);
  List< unsigned long long > countSum(const list_t& list);
  void outputValue(std::ostream& out, const list_t& list);
}
#endif
