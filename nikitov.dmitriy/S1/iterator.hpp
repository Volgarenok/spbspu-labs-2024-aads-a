#ifndef ITERATOR_HPP
#define ITERATIR_HPP

#include "list.hpp"

namespace nikitov
{
  template< typename T >
  struct Iterator
  {
    List< T >* node;
  };
}
#endif
