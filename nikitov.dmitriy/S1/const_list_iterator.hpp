#ifndef CONST_LIST_ITERATOR_HPP
#define CONST_LIST_ITERATOR_HPP

#include <iterator>
#include "list_iterator.hpp"

namespace nikitov
{
  template< typename T >
  class ListIterator;

  template< typename T >
  class Node;

  template< typename T >
  class ConstListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class ListIterator< T >;
  public:
    ConstListIterator(Node< T >* node);
    ConstListIterator(const ConstListIterator< T >&) = default;
    ~ConstListIterator() = default;

    const T& operator*() const;
    const T* operator->() const;
    ConstListIterator< T >& operator=(const ConstListIterator< T >&) = default;
    ConstListIterator< T >& operator++();
    ConstListIterator< T > operator++(int);
    ConstListIterator< T >& operator--();
    ConstListIterator< T > operator--(int);
    bool operator==(const ListIterator< T >& other) const;
    bool operator!=(const ListIterator< T >& other) const;
    bool operator==(const ConstListIterator< T >& other) const;
    bool operator!=(const ConstListIterator< T >& other) const;

    ConstListIterator< T >& advance(int n);

  private:
    const Node< T >* node_;
  };

  template< typename T >
  ConstListIterator< T >::ConstListIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  const T& ConstListIterator< T >::operator*() const
  {
    if (node_->next_ == nullptr)
    {
      throw std::logic_error("Error: Dereferencing of std::end()");
    }
    return node_->value_;
  }

  template< typename T >
  const T* ConstListIterator< T >::operator->() const
  {
    if (node_->next_ == nullptr)
    {
      throw std::logic_error("Error: Dereferencing of std::end()");
    }
    return std::addressof(node_->value_);
  }

  template< typename T >
  ConstListIterator< T >& ConstListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ConstListIterator< T > ConstListIterator< T >::operator++(int)
  {
    ConstListIterator temp(*this);
    node_ = node_->next_;
    return temp;
  }

  template< typename T >
  ConstListIterator< T >& ConstListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ConstListIterator< T > ConstListIterator< T >::operator--(int)
  {
    ConstListIterator temp(*this);
    node_ = node_->prev_;
    return temp;
  }

  template< typename T >
  bool ConstListIterator< T >::operator==(const ListIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ConstListIterator< T >::operator!=(const ListIterator< T >& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  bool ConstListIterator< T >::operator==(const ConstListIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ConstListIterator< T >::operator!=(const ConstListIterator< T >& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  ConstListIterator< T >& ConstListIterator< T >::advance(int n)
  {
    if (n > 0)
    {
      for (int i = 0; i != n; ++i)
      {
        node_ = node_->next_;
      }
    }
    else if (n < 0)
    {
      for (int i = 0; i != -n; ++i)
      {
        node_ = node_->prev_;
      }
    }
    return *this;
  }
}
#endif
