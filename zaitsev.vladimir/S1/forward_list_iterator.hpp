#ifndef FORWARD_LIST_ITERATOR_HPP
#define FORWARD_LIST_ITERATOR_HPP
#include <stdexcept>
#include <iterator>
#include "node.hpp"

namespace zaitsev
{
  template< typename T >
  class ForwardListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ForwardListIterator();
    ForwardListIterator(Node* node);
    ForwardListIterator(const ForwardListIterator&) = default;
    ~ForwardListIterator() = default;
    ForwardListIterator& operator=(const ForwardListIterator&) = default;
    ForwardListIterator& operator++();
    ForwardListIterator operator++(int);
    T& operator*();
    T* operator->();
    bool operator!=(const ForwardListIterator& other) const;
    bool operator==(const ForwardListIterator& other) const;
  private:
    Node< T >* node_;
  };

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator():
    node_(nullptr)
  {}

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(Node< T >*node):
    node_(node)
  {}

  template< typename T >
  ForwardListIterator< T >& ForwardListIterator< T >::operator++()
  {
    if (!node_)
    {
      throw std::runtime_error("Iterator is out of range");
    }
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    ForwardListIterator< T > res = *this;
    if (!node_)
    {
      throw std::runtime_error("Iterator is out of range");
    }
    ++(*this);
    return res;
  }

  template< typename T >
  T& ForwardListIterator< T >::operator*()
  {
    return this->node_->value_;
  }

  template< typename T >
  T* ForwardListIterator< T >::operator->()
  {
    return std::addressof(this->node_->value_);
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const ForwardListIterator& other) const
  {
    return node_ !=other.node_;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator==(const ForwardListIterator& other) const
  {
    return node_ == other.node_;
  }
}
#endif
