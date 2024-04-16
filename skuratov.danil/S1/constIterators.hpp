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

    ConstIterator< T >& operator=(const ConstIterator< T >& different) = default;
    ConstIterator< T >& operator++();
    ConstIterator< T >& operator--();
    ConstIterator< T > operator++(int);
    ConstIterator< T > operator--(int);

  private:
    Node< T >* node_;
    ConstIterator(Node< T >* node_);
  };
}

#endif
