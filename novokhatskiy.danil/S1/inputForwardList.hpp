#ifndef INPUT_FORWARD_LIST_HPP
#define INPUT_FORWARD_LIST_HPP
#include <istream>
#include <string>
#include "forward_list_iterators.hpp"
#include "forward_list.hpp"

namespace novokhatskiy
{
  void inputForwardList(novokhatskiy::ForwardList<std::pair<std::string, novokhatskiy::ForwardList< unsigned long long > > >& pairsOfList, std::istream& input);
}

#endif 
