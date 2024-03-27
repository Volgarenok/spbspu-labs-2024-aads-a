#ifndef FUNCS_HPP
#define FUNCS_HPP
#include "iterator.hpp"

namespace zakozhurnikova
{
  template < typename T >
  void fill(Iterator< T > first, Iterator< T > last, const T& value)
  {
    for (Iterator< T > it = first; it != last; ++it)
    {
      *it = value;
    }
  }
}

#endif
