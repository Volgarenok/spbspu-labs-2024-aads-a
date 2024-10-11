#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <stddef.h>
#include <memory>

#include "node.hpp"

namespace kovtun
{
  template< typename T >
  class List;

  template< typename T >
  class ConstIterator
  {
  public:
    using this_t = ConstIterator< T >;

    friend class List< T >;

    ConstIterator() = default;
    ~ConstIterator() = default;
    ConstIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;

    this_t & operator++();
    this_t & operator++(int);

    bool operator==(const this_t &rhs) const;
    bool operator!=(const this_t &rhs) const;

    T & operator*() const;
    T * operator->() const;

    this_t & operator--();
    this_t & operator--(int);

  private:
    Node<T> *node_;

    explicit ConstIterator(Node< T > * node);
  };

  template< typename T >
  ConstIterator< T >::ConstIterator(Node< T > * node) :
    node_(node)
  {}

  template< typename T >
  ConstIterator< T > & ConstIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ConstIterator< T > & ConstIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  bool ConstIterator< T >::operator==(const this_t &rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ConstIterator< T >::operator!=(const this_t &rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  T & ConstIterator< T >::operator*() const
  {
    return node_->val;
  }

  template< typename T>
  T * ConstIterator< T >::operator->() const
  {
    return std::addressof(node_->val);
  }

  template< typename T>
  ConstIterator< T > & ConstIterator< T >::operator--()
  {
    node_ = node_->prev;
    return node_;
  }

  template< typename T>
  ConstIterator< T > & ConstIterator< T >::operator--(int)
  {
    this_t result(*this);
    --(*this);
    return result;
  }
}

#endif
