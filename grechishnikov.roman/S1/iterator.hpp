#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include "node.hpp"

namespace grechishnikov
{
  template< typename T >
  class Iterator
  {
  public:
    Iterator();
    Iterator(Node< T >* node);
    Iterator(const Iterator< T >& other);

    T& operator*();
    T* operator->();

    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    Node< T >& operator[](size_t);

    bool operator==(const Iterator< T >& other);
    bool operator!=(const Iterator< T >& other);

  private:
    Node< T >* node_;
  };

  template< typename T >
  Iterator< T >::Iterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  Iterator< T >::Iterator(const Iterator< T >& other):
    node_(other.node_)
  {}

  template< typename T >
  T& Iterator< T >::operator*()
  {
    return node_->data_;
  }

  template< typename T >
  T* Iterator< T >::operator->()
  {
    return &node_->data_;
  }

  template< typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  Iterator< T >& Iterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator< T > temp(*this);
    operator++();
    return temp;
  }

  template< typename T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    Iterator< T > temp(*this);
    operator--();
    return temp;
  }

  template< typename T >
  Node< T >& Iterator< T >::operator[](size_t pos)
  {
    for(size_t i = 0; i < pos; i++)
    {
      operator++();
    }
    return *node_;
  }

  template< typename T >
  bool Iterator< T >::operator==(const Iterator< T >& other)
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& other)
  {
    return !(node_ == other.node_);
  }


}

#endif
