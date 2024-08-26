#ifndef LIST_CONST_ITERATOR
#define LIST_CONST_ITERATOR

#include <utility>
#include <iterator>
#include "node.hpp"
#include "list_iterator.hpp"

namespace erohin
{
  template < class T >
  class List;

  template< class T >
  class ListConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ListConstIterator();
    ListConstIterator(const ListConstIterator< T > &) = default;
    ~ListConstIterator() = default;
    ListConstIterator< T > & operator=(const ListConstIterator< T > &) = default;
    ListConstIterator< T > & operator++();
    ListConstIterator< T > operator++(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const ListConstIterator< T > & rhs) const;
    bool operator!=(const ListConstIterator< T > & rhs) const;
  private:
    const detail::Node< T > * node_;
    explicit ListConstIterator(const detail::Node< T > * node_ptr);
  };

  template< class T >
  ListConstIterator< T >::ListConstIterator():
    node_(nullptr)
  {}

  template< class T >
  ListConstIterator< T >::ListConstIterator(const detail::Node< T > * node_ptr):
    node_(node_ptr)
  {}

  template< class T >
  ListConstIterator< T > & ListConstIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
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
  bool ListConstIterator< T >::operator==(const ListConstIterator< T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class T >
  bool ListConstIterator< T >::operator!=(const ListConstIterator< T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
