#ifndef FORWARD_LIST_ITERATOR_HPP
#define FORWARD_LIST_ITERATOR_HPP
#include <stdexcept>
#include <iterator>
#include "node.hpp"
#include "forward_list_const_iterator.hpp"

namespace zaitsev
{
  template< typename T >
  class ForwardListIterator: public ConstForwardListIterator< T >
  {
  public:
    using const_base = ConstForwardListIterator< T >;
    ForwardListIterator() = default;
    ForwardListIterator(Node< T >* node);
    ForwardListIterator& operator++();
    ForwardListIterator operator++(int);
    T& operator*();
    T* operator->();
  };

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(Node< T >* node):
    const_base(node)
  {}

  template< typename T >
  ForwardListIterator< T >& ForwardListIterator< T >::operator++()
  {
    const_base::operator++();
    return *this;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    ForwardListIterator< T > res = *this;
    const_base::operator++();
    return res;
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*()
  {
    return const_base::node_->value_;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->()
  {
    return std::addressof(const_base::node_->value_);
  }
}
#endif
