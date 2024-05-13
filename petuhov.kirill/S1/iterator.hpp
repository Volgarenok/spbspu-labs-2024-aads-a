#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include "node.hpp"

namespace petuhov
{
  template < typename T >
  class List;

  template < typename T >
  class Iterator
  {
    friend class List< T >;

  public:
    Iterator();
    Iterator(const Iterator &iter) = default;

    T &operator*() const;
    T *operator->() const;
    Iterator &operator++();
    Iterator operator++(int);
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;

    ~Iterator() = default;

  private:
    Node< T > *node_;
  };

  template < typename T >
  Iterator< T >::Iterator() : node_(nullptr)
  {
  }

  template < typename T >
  T &Iterator< T >::operator*() const
  {
    return node_->value_;
  }

  template < typename T >
  T *Iterator< T >::operator->() const
  {
    return &(operator*());
  }

  template < typename T >
  Iterator< T > &Iterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    Iterator< T > temp = *this;
    node_ = node_->next_;
    return temp;
  }

  template < typename T >
  bool Iterator< T >::operator==(const Iterator &other) const
  {
    return node_ == other.node_;
  }

  template < typename T >
  bool Iterator< T >::operator!=(const Iterator &other) const
  {
    return node_ != other.node_;
  }
}

#endif
