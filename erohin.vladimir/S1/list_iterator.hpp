#ifndef LIST_ITERATOR
#define LIST_ITERATOR

#include <utility>
#include "node.hpp"

namespace erohin
{
  template < class T >
  class List;

  template< class T >
  class ListIterator
  {
    friend class List< T >;
  public:
    ListIterator();
    ListIterator(const ListIterator< T > &) = default;
    ListIterator(const Node< T > * node_ptr);
    ~ListIterator() = default;
    ListIterator< T > & operator=(const ListIterator< T > &) = default;
    ListIterator< T > & operator++();
    ListIterator< T > operator++(int);
    ListIterator< T > operator+(int number);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
    bool operator==(const ListIterator< T > & rhs);
    bool operator!=(const ListIterator< T > & rhs);
  private:
    Node< T > * node_;
  };

  template< class T >
  ListIterator< T >::ListIterator():
    node_(nullptr)
  {}

  template< class T >
  ListIterator< T >::ListIterator(const Node< T > * node_ptr):
    node_(const_cast< Node< T > * >(node_ptr))
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
  ListIterator< T > ListIterator< T >::operator+(int number)
  {
    ListIterator< T > result = *this;
    for (int i = 0; i < number; ++i)
    {
      ++result;
    }
    return result;
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
  bool ListIterator< T >::operator==(const ListIterator< T > & rhs)
  {
    return (node_ == rhs.node_);
  }

  template< class T >
  bool ListIterator< T >::operator!=(const ListIterator< T > & rhs)
  {
    return !(operator==(rhs));
  }

  template< class T >
  bool operator==(const ListIterator< T > & lhs, const ListIterator< T > & rhs)
  {
    return (lhs.node_ == rhs.node_);
  }

  template< class T >
  bool operator!=(const ListIterator< T > & lhs, const ListIterator< T > & rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
