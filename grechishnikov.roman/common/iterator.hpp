#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "node.hpp"

namespace grechishnikov
{
  template< typename T >
  class List;

  template< typename T >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    Iterator();
    Iterator(const Iterator< T >& other);
    ~Iterator() = default;

    T& operator*();
    T* operator->();

    Iterator& operator=(const Iterator< T >& other) = default;
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    bool operator==(const Iterator< T >& other) const;
    bool operator!=(const Iterator< T >& other) const;

    friend List< T >;

  private:
    explicit Iterator(detail::Node< T >* node);
    detail::Node< T >* node_;
  };

  template< typename T >
  Iterator< T >::Iterator(detail::Node< T >* node):
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
  bool Iterator< T >::operator==(const Iterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& other) const
  {
    return !(node_ == other.node_);
  }

}

#endif
