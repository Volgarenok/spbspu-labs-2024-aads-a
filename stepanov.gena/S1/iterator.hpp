#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace stepanov
{
  template < typename T>
  class List;

  template < typename T>
  class Iterator
  {
    public:
      Iterator():
        node_(nullptr)
      {}
      Iterator(Node< T > * node):
        node_(node)
      {}
      ~Iterator() = default;

    private:
      Node * node_;
  }
}


#endif
