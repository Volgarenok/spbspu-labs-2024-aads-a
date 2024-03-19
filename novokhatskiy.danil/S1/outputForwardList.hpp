#ifndef OUTPUT_FORWARD_LIST_HPP
#define OUTPUT_FORWARD_LIST_HPP
#include "forward_list_iterators.hpp"
#include "forward_list.hpp"

namespace novokhatskiy
{
  void outputForwardList(std::ostream& out, ForwardList< std::pair< std::string, ForwardList< size_t > > >& pairs);
}

#endif
