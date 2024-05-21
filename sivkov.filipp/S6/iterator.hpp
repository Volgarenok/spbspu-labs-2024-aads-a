#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace sivkov
{
  template < typename T >
  class List;

  template < typename T >
  class Iterator
  {
    friend class List< T >;
  public:
    Iterator();

    Iterator< T >& operator=(const Iterator< T >&) = default;
    Iterator(const Iterator< T >&) = default;
    ~Iterator() = default;

    T& operator*();
    T* operator->();

    bool operator!=(const Iterator< T >& other) const;
    bool operator==(const Iterator< T >& other) const;
    const T& operator*() const;
    const T* operator->() const;
    Iterator< T >& operator++();
    Iterator< T > operator++(int);

  private:
    detail::Node< T >* node_;
    explicit Iterator(detail::Node< T >* node);
  };

  template< typename T >
  Iterator< T >::Iterator(detail::Node< T >* node):
    node_(node)
  {}

  template< typename T >
  Iterator< T >::Iterator() :
    node_(nullptr)
  {}

  template< typename T >
  T& Iterator< T >::operator*()
  {
    return node_->data;
  }

  template< typename T >
  T* Iterator< T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template< typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  bool Iterator< T >::operator==(const Iterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  const T& Iterator< T >::operator*() const
  {
    return node_->data;
  }

  template< typename T >
  const T* Iterator< T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    if (node_ != nullptr)
    {
      node_ = node_->next;
    }
    return *this;
  }

  template< typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator< T > result(*this);
    ++(*this);
    return result;
  }
}

#endif

