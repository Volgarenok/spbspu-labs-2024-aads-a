#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

namespace baranov
{
  template< class T >
  class Iterator
  {
    public:
      Iterator();
    private:
      Node< T > * node_;
  };

  template< class T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}
}

#endif

