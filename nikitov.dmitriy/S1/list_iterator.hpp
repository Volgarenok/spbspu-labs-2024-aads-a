#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>
#include "const_list_iterator.hpp"

namespace nikitov
{
  template< typename T >
  class ConstListIterator;

  template< typename T >
  class Node;

  template< typename T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class ConstListIterator< T >;
  public:
    ListIterator(Node< T >* node);
    ListIterator(const ListIterator< T >&) = default;
    ~ListIterator() = default;

    T& operator*();
    T* operator->();
    ListIterator< T >& operator=(const ListIterator< T >&) = default;
    ListIterator< T >& operator++();
    ListIterator< T > operator++(int);
    ListIterator< T >& operator--();
    ListIterator< T > operator--(int);
    bool operator==(const ConstListIterator< T >& other) const;
    bool operator!=(const ConstListIterator< T >& other) const;
    bool operator==(const ListIterator< T >& other) const;
    bool operator!=(const ListIterator< T >& other) const;

    ListIterator< T >& advance(int n);

  private:
    Node< T >* node_;
  };

  template< typename T >
  ListIterator< T >::ListIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  T& ListIterator< T >::operator*()
  {
    if (node_->next_ == nullptr)
    {
      throw std::logic_error("Error: Dereferencing of std::end()");
    }
    return node_->value_;
  }

  template< typename T >
  T* ListIterator< T >::operator->()
  {
    if (node_->next_ == nullptr)
    {
      throw std::logic_error("Error: Dereferencing of std::end()");
    }
    return std::addressof(node_->value_);
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ListIterator< T > ListIterator< T >::operator++(int)
  {
    ListIterator temp(*this);
    node_ = node_->next_;
    return temp;
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ListIterator< T > ListIterator< T >::operator--(int)
  {
    ListIterator temp(*this);
    node_ = node_->prev_;
    return temp;
  }

  template< typename T >
  bool ListIterator< T >::operator==(const ConstListIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ListIterator< T >::operator!=(const ConstListIterator< T >& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  bool ListIterator< T >::operator==(const ListIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ListIterator< T >::operator!=(const ListIterator< T >& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::advance(int n)
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
