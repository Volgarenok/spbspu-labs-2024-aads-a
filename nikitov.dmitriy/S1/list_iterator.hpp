#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace nikitov
{
  template< class T >
  class List;

  template< class T >
  class Node;

  template< class T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  private:
    ListIterator(detail::Node< T >* node);

  public:
    ListIterator(const ListIterator< T >&) = default;
    ~ListIterator() = default;

    ListIterator< T >& operator=(const ListIterator< T >&) = default;

    ListIterator< T >& operator++();
    ListIterator< T > operator++(int);
    ListIterator< T >& operator--();
    ListIterator< T > operator--(int);

    T& operator*();
    T* operator->();

    bool operator==(const ListIterator< T >& other) const;
    bool operator!=(const ListIterator< T >& other) const;

  private:
    detail::Node< T >* node_;
  };

  template< class T >
  ListIterator< T >::ListIterator(detail::Node< T >* node):
    node_(node)
  {}

  template< class T >
  ListIterator< T >& ListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< class T >
  ListIterator< T > ListIterator< T >::operator++(int)
  {
    ListIterator< T > temp(*this);
    node_ = node_->next_;
    return temp;
  }

  template< class T >
  ListIterator< T >& ListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< class T >
  ListIterator< T > ListIterator< T >::operator--(int)
  {
    ListIterator< T > temp(*this);
    node_ = node_->prev_;
    return temp;
  }

  template< class T >
  T& ListIterator< T >::operator*()
  {
    return node_->value_;
  }

  template< class T >
  T* ListIterator< T >::operator->()
  {
    return std::addressof(node_->value_);
  }

  template< class T >
  bool ListIterator< T >::operator==(const ListIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< class T >
  bool ListIterator< T >::operator!=(const ListIterator< T >& other) const
  {
    return node_ != other.node_;
  }
}
#endif
