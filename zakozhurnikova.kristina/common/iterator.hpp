#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <memory>
#include <iterator>
#include "node.hpp"

namespace zakozhurnikova
{
  template < class T >
  class List;

  template < typename T >
  struct Iterator: public std::iterator < std::bidirectional_iterator_tag, T >
  {
    friend struct List< T >;
    using this_t = Iterator< T >;
    Iterator();
    Iterator(const this_t&) = default;
    ~Iterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    this_t& operator--();
    this_t operator--(int);
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;

  private:
    detail::Node< T >* node_;
    explicit Iterator(detail::Node< T > * node_ptr);
  };

  template < typename T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}

  template < typename T >
  Iterator< T >::Iterator(detail::Node< T >* node):
    node_(node)
  {}

  template < typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    node_ = node_->next;
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator< T > result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  Iterator< T >& Iterator< T >::operator--()
  {
    node_ = node_->prev;
    return *this;
  }


  template < typename T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    Iterator< T > result(*this);
    --(*this);
    return result;
  }

  template < typename T >
  bool Iterator< T >::operator==(const Iterator< T >& rhs) const
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& rhs) const
  {
    return !(*this == rhs);
  }

  template < typename T >
  T& Iterator< T >::operator*()
  {
    return node_->data;
  }

  template < typename T >
  const T& Iterator< T >::operator*() const
  {
    return node_->data;
  }

  template < typename T >
  T* Iterator< T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template < typename T >
  const T* Iterator< T >::operator->() const
  {
    return std::addressof(node_->data);
  }
}

#endif
