#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <iterator>
#include <cassert>
#include "node.hpp"

namespace stepanov
{
  template < typename T >
  class List;

  template < typename T >
  class ConstIterator: std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;

  public:
    ConstIterator():
      node_(nullptr)
    {}
    ConstIterator(Node< T > * node):
      node_(node)
    {}
    ~ConstIterator() = default;
  private:
    Node< T > * node_;
  };
}

#endif
