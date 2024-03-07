#ifndef NAMED_NUMBER_LIST_HPP
#define NAMED_NUMBER_LIST_HPP

#include <string>
#include "list.hpp"

namespace erohin
{
  struct named_list
  {
    std::string name;
    List< int > number_list;
  };
}

#endif
