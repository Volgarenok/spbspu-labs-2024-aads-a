#ifndef LIST_FUNCTIONS_HPP
#define LIST_FUNCTIONS_HPP

#include <iostream>
#include "list.hpp"

namespace baranov
{
  using ds_t = List< std::pair< std::string, List< size_t > > >;
  using listOfLists = List< List< size_t > >;
  void readByElement(listOfLists &, ds_t &);
}

#endif
