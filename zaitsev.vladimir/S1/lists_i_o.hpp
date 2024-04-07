#ifndef LISTS_I_O_HPP
#define LISTS_I_O_HPP
#include <string>
#include "forward_list.hpp"

namespace zaitsev
{
  using ull = unsigned long long;
  using ullList = ForwardList< ull >;
  using named_ullList = std::pair< std::string, ullList >;
  void input_lists(ForwardList< named_ullList >& list);
  ullList* print_lists(ForwardList< named_ullList >& list);
  void print_sums(ullList& sums);
}
#endif
