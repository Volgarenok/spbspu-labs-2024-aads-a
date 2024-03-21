#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <iostream>
#include "list.hpp"

namespace baranov
{
  using ds_t = List< std::pair< std::string, List< size_t > > >;
  void inputList(std::istream &, ds_t & list);
}

#endif

