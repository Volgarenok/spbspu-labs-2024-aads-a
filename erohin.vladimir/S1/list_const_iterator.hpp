#ifndef LIST_CONST_ITERATOR
#define LIST_CONST_ITERATOR

#include <utility>
#include "node.hpp"

namespace erohin
{
  template< class T >
  class ListConstIterator
  {
  public:
    const Node< T > * node_;
    ListConstIterator();
    ListConstIterator(const Node< T > * const node_ptr);
    ListConstIterator(const ListConstIterator< T > &) = default;
    ~ListConstIterator() = default;
    ListConstIterator< T > & operator=(const ListConstIterator< T > &) = default;
    ListConstIterator< T > & operator++();
    ListConstIterator< T > operator++(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const ListConstIterator< T > & rhs);
    bool operator!=(const ListConstIterator< T > & rhs);
  };

  template< class T >
  ListConstIterator< T >::ListConstIterator():
    node_(nullptr)
  {}

  template< class T >
  ListConstIterator< T >::ListConstIterator(const Node< T > * const node_ptr):
    node_(node_ptr)
  {}

  template< class T >
  ListConstIterator< T > & ListConstIterator< T >::operator++()
  {
    node_ = node_->next_;
    return this;
  }

  template< class T >
  ListConstIterator< T > ListConstIterator< T >::operator++(int)
  {
    ListConstIterator< T > prev = *this;
    node_ = node_->next_;
    return prev;
  }

  template< class T >
  const T & ListConstIterator< T >::operator*() const
  {
    return node_->data_;
  }

  template< class T >
  const T * ListConstIterator< T >::operator->() const
  {
    return std::addressof(node_->data_);
  }

  template< class T >
  bool ListConstIterator< T >::operator==(const ListConstIterator< T > & rhs)
  {
    return (node_ == rhs.node_);
  }

  template< class T >
  bool ListConstIterator< T >::operator!=(const ListConstIterator< T > & rhs)
  {
    return !(operator==(rhs));
  }
}

#endif
