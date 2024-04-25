#ifndef CONST_ITERATORS_HPP
#define CONST_ITERATORS_HPP

#include "node.hpp"

namespace skuratov
{
  template < typename T >
  class List;

  template < typename T >
  class ConstIterator
  {
    friend List< T >;

  public:
    ConstIterator();
    ConstIterator(const ConstIterator< T >& different);
    ~ConstIterator() = default;

    const T& operator*();
    const T* operator->();

    bool operator==(const ConstIterator< T >& different) const;
    bool operator!=(const ConstIterator< T >& different) const;

    ConstIterator< T >& operator=(const ConstIterator< T >& different);
    ConstIterator< T >& operator++();
    ConstIterator< T >& operator--();
    ConstIterator< T > operator++(int);
    ConstIterator< T > operator--(int);

  private:
    Node< T >* node_;
    ConstIterator(Node< T >* node_);
  };

  template< typename T >
  ConstIterator< T >::ConstIterator()
  {}

  template< typename T >
  ConstIterator< T >::ConstIterator(const ConstIterator< T >& different)
  {}

  template< typename T >
  const T& ConstIterator< T >::operator*()
  {
    return;
  }

  template< typename T >
  const T* ConstIterator< T >::operator->()
  {
    return nullptr;
  }

  template< typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T >& different) const
  {
    return false;
  }

  template< typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T >& different) const
  {
    return false;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator=(const ConstIterator< T >& different)
  {
    return;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator++()
  {
    return;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator--()
  {
    return;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    return ConstIterator< T >();
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    return ConstIterator< T >();
  }
}

#endif
