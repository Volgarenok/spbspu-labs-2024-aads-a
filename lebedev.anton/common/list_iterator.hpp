#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>
#include "list_node.hpp"

namespace lebedev
{
  template< class T >
  class List;

  template< class T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ListIterator();
    ListIterator(const ListIterator< T > &) = default;
    ~ListIterator() = default;

    ListIterator< T > & operator=(const ListIterator< T > &) = default;
    ListIterator< T > & operator++();
    ListIterator< T > operator++(int);
    ListIterator< T > & operator--();
    ListIterator< T > operator--(int);

    bool operator==(const ListIterator< T > & rhs) const;
    bool operator!=(const ListIterator< T > & rhs) const;

    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
  private:
    detail::Node< T > * node_;
    explicit ListIterator(detail::Node< T > * node);
  };

  template< class T >
  ListIterator< T >::ListIterator():
    node_(nullptr)
  {}

  template< class T >
  ListIterator< T >::ListIterator(detail::Node< T > * node):
    node_(node)
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
    ListIterator< T > temp = *this;
    node_ = node_->next_;
    return temp;
  }

  template< class T >
  ListIterator< T > & ListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< class T >
  ListIterator< T > ListIterator< T >::operator--(int)
  {
    ListIterator< T > temp = *this;
    node_ = node_->prev_;
    return temp;
  }

  template< class T >
  bool ListIterator< T >::operator==(const ListIterator< T > & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class T >
  bool ListIterator< T >::operator!=(const ListIterator< T > & rhs) const
  {
    return !(node_ == rhs.node_);
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
}

#endif
