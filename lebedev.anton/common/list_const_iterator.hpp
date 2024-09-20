#ifndef CONST_LIST_ITERATOR_HPP
#define CONST_LIST_ITERATOR_HPP

#include <iterator>
#include "list_node.hpp"

namespace lebedev
{
  template< class T >
  class List;

  template< class T >
  class ConstListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ConstListIterator();
    ConstListIterator(const ConstListIterator< T > &) = default;
    ~ConstListIterator() = default;

    ConstListIterator< T > & operator=(const ConstListIterator< T > &) = default;
    ConstListIterator< T > & operator++();
    ConstListIterator< T > operator++(int);
    ConstListIterator< T > & operator--();
    ConstListIterator< T > operator--(int);

    bool operator==(const ConstListIterator< T > & rhs) const;
    bool operator!=(const ConstListIterator< T > & rhs) const;

    const T & operator*() const;
    const T * operator->() const;
  private:
    detail::Node< T > * node_;
    explicit ConstListIterator(detail::Node< T > * node);
  };

  template< class T >
  ConstListIterator< T >::ConstListIterator() :
    node_(nullptr)
  {}

  template< class T >
  ConstListIterator< T >::ConstListIterator(detail::Node< T > * node):
    node_(node)
  {}

  template< class T >
  ConstListIterator< T > & ConstListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< class T >
  ConstListIterator< T > ConstListIterator< T >::operator++(int)
  {
    ConstListIterator< T > temp = *this;
    node_ = node_->next_;
    return temp;
  }

  template< class T >
  ConstListIterator< T > & ConstListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< class T >
  ConstListIterator< T > ConstListIterator< T >::operator--(int)
  {
    ConstListIterator< T > temp = *this;
    node_ = node_->prev_;
    return temp;
  }

  template< class T >
  bool ConstListIterator< T >::operator==(const ConstListIterator< T > & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class T >
  bool ConstListIterator< T >::operator!=(const ConstListIterator< T > & rhs) const
  {
    return !(node_ == rhs.node_);
  }

  template< class T >
  const T & ConstListIterator< T >::operator*() const
  {
    return node_->data_;
  }

  template< class T >
  const T * ConstListIterator< T >::operator->() const
  {
    return std::addressof(node_->data_);
  }
}

#endif
