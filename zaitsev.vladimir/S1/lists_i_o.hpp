#ifndef LISTS_I_O_HPP
#define LISTS_I_O_HPP
#include <string>
#include <iostream>
#include <forward_list.hpp>

namespace zaitsev
{
  using ull = unsigned long long;
  using ullList = ForwardList< ull >;
  using named_ullList = std::pair< std::string, ullList >;
  void input_lists(ForwardList< named_ullList >& list);
  ullList print_lists(std::ostream& out, ForwardList< named_ullList >& list);
  std::ostream& print_sums(std::ostream& out, ullList& sums);
}
#endif
