#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace baranov
{
  template< class T >
  class Iterator
  {
    public:
      using this_t = Iterator< T >;

      Iterator();
      Iterator(Node< T > * node);
      ~Iterator() = default;
      Iterator(const this_t &) = default;
      this_t & operator=(const this_t &) = default;

      this_t & operator++();
      this_t operator ++(int);

      this_t & operator--();
      this_t operator --(int);

      this_t operator+(size_t);
      this_t operator-(size_t);

      T & operator*();
      T * operator->();

      bool operator==(const this_t &) const;
      bool operator!=(const this_t &) const;
    private:
      Node< T > * node_;
  };

  template< class T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}

  template< class T >
  Iterator< T >::Iterator(Node< T > * node):
    node_(node)
  {}

  template< class T >
  Iterator< T > & Iterator< T >::operator++()
  {
    assert(node_ != nullptr);
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return * this;
  }

  template< class T >
  Iterator< T > & Iterator< T >::operator--()
  {
    assert(node_ != nullptr);
    Iterator temp = *this;
    --(*this);
    return temp;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return * this;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator+(size_t rhs)
  {
    assert(node_ != nullptr);
    for (size_t i; i < rhs; ++i)
    {
      ++(*this);
    }
    return * this;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator-(size_t rhs)
  {
    assert(node_ != nullptr);
    for (size_t i; i < rhs; ++i)
    {
      --(*this);
    }
    return * this;
  }

  template< class T >
  T & Iterator< T >::operator*() {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< class T >
  T * Iterator< T >::operator->() {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< class T >
  bool Iterator< T >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class T >
  bool Iterator< T >::operator!=(const this_t & rhs) const
  {
    return !(rhs == *this);
  }
}

#endif

