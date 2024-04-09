#ifndef FUNCS_HPP
#define FUNCS_HPP
#include "iterator.hpp"
#include <algorithm>

namespace zakozhurnikova
{
  template < typename It, typename T >
  void fill(It first, It last, const T& value)
  {
    std::fill(first, last, value);
  }
}

#endif
