#ifndef LIST_ITERATOR
#define LIST_ITERATOR

#include <utility>
#include <iterator>
#include "node.hpp"

namespace erohin
{
  template < class T >
  class List;

  template< class T >
  class ListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ListIterator();
    ListIterator(const ListIterator< T > &) = default;
    ~ListIterator() = default;
    ListIterator< T > & operator=(const ListIterator< T > &) = default;
    ListIterator< T > & operator++();
    ListIterator< T > operator++(int);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
    bool operator==(const ListIterator< T > & rhs) const;
    bool operator!=(const ListIterator< T > & rhs) const;
  private:
    detail::Node< T > * node_;
    explicit ListIterator(detail::Node< T > * node_ptr);
  };

  template< class T >
  ListIterator< T >::ListIterator():
    node_(nullptr)
  {}

  template< class T >
  ListIterator< T >::ListIterator(detail::Node< T > * node_ptr):
    node_(node_ptr)
  {}

  template< class T >
  ListIterator< T > & ListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< class T >
  ListIterator< T > ListIterator< T >::operator++(int)
  {
    ListIterator< T > prev = *this;
    node_ = node_->next_;
    return prev;
  }

  template< class T >
  T & ListIterator< T >::operator*()
  {
    return node_->data_;
  }

  template< class T >
  const T & ListIterator< T >::operator*() const
  {
    return node_->data_;
  }

  template< class T >
  T * ListIterator< T >::operator->()
  {
    return std::addressof(node_->data_);
  }

  template< class T >
  const T * ListIterator< T >::operator->() const
  {
    return std::addressof(node_->data_);
  }

  template< class T >
  bool ListIterator< T >::operator==(const ListIterator< T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class T >
  bool ListIterator< T >::operator!=(const ListIterator< T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
