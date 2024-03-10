#ifndef LISTS_I_O_HPP
#define LISTS_I_O_HPP
#include <string>
#include "forward_list.hpp"

namespace zaitsev
{
  using ull = unsigned long long;
  void input_lists(ForwardList< std::pair< std::string, ForwardList< ull > > >& list);
  ForwardList< ull >* print_lists(ForwardList< std::pair< std::string, ForwardList< ull > > >& list);
  void print_sums(ForwardList< ull >& sums);
}
#endif
