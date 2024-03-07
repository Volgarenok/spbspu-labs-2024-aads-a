#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

namespace baranov
{
  template< class T >
  class Iterator
  {
    public:
      using this_t = Iterator< T >;

      Iterator();
      ~Iterator() = default;
      Iterator(const this_t &) = default;
      this_t & operator=(const this_t &) = default;
    private:
      Node< T > * node_;
  };

  template< class T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}
}

#endif

