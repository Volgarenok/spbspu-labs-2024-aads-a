#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <memory>
#include <cassert>
#include "node.hpp"

namespace baranov
{
  template< class T >
  class ConstIterator: public std::iterator < std::bidirectional_iterator_tag, T >
  {
    public:
      using this_t = ConstIterator< T >;

      ConstIterator();
      explicit ConstIterator(Node< T > * node);
      ~ConstIterator() = default;
      ConstIterator(const this_t &) = default;
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
  ConstIterator< T >::ConstIterator():
    node_(nullptr)
  {}

  template< class T >
  ConstIterator< T >::ConstIterator(Node< T > * node):
    node_(node)
  {}

  template< class T >
  ConstIterator< T > & ConstIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return * this;
  }

  template< class T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result = *this;
    ++(*this);
    return result;
  }

  template< class T >
  ConstIterator< T > & ConstIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return * this;
  }

  template< class T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result = *this;
    --(*this);
    return result;
  }

  template< class T >
  ConstIterator< T > ConstIterator< T >::operator+(size_t rhs)
  {
    assert(node_ != nullptr);
    for (size_t i = 0; i < rhs; ++i)
    {
      ++(*this);
    }
    return * this;
  }

  template< class T >
  ConstIterator< T > ConstIterator< T >::operator-(size_t rhs)
  {
    assert(node_ != nullptr);
    for (size_t i = 0; i < rhs; ++i)
    {
      --(*this);
    }
    return * this;
  }

  template< class T >
  T & ConstIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< class T >
  T * ConstIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< class T >
  bool ConstIterator< T >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class T >
  bool ConstIterator< T >::operator!=(const this_t & rhs) const
  {
    return !(rhs == *this);
  }
}

#endif

