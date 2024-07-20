#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include <cassert>
#include "node.hpp"

namespace baranov
{
  template < class T >
  class List;

  template< class T >
  class Iterator: public std::iterator < std::bidirectional_iterator_tag, T >
  {
    public:
      friend class List< T >;
      using this_t = Iterator< T >;

      Iterator();
      ~Iterator() = default;
      Iterator(const this_t &) = default;
      this_t & operator=(const this_t &) = default;

      this_t & operator++();
      this_t operator ++(int);

      this_t & operator--();
      this_t operator --(int);

      T & operator*();
      T * operator->();
      const T & operator*() const;
      const T * operator->() const;

      bool operator==(const this_t &) const;
      bool operator!=(const this_t &) const;
    private:
      Node< T > * node_;
      explicit Iterator(Node< T > * node);
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
    node_ = node_->next_;
    return * this;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result = * this;
    ++(*this);
    return result;
  }

  template< class T >
  Iterator< T > & Iterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return * this;
  }

  template< class T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result = * this;
    --(*this);
    return result;
  }

  template< class T >
  T & Iterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< class T >
  T * Iterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< class T >
  const T & Iterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< class T >
  const T * Iterator< T >::operator->() const
  {
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

