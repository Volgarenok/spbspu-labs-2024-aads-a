#ifndef CONST_ITARATOR_HPP
#define CONST_ITERATOR_HPP

#include <cstddef>
#include "node.hpp"

namespace grechishnikov
{
  template< typename T >
  class ConstIterator
  {
  public:
    ConstIterator();
    ConstIterator(Node< T >* node);
    ConstIterator(const ConstIterator< T >& other);
    ~ConstIterator() = default;

    const T& operator*();
    const T* operator->();

    ConstIterator& operator=(const ConstIterator< T >& other) = default;
    ConstIterator& operator++();
    ConstIterator& operator--();
    ConstIterator operator++(int);
    ConstIterator operator--(int);

    ConstIterator operator+(size_t);
    ConstIterator operator-(size_t);

    ConstIterator& operator[](size_t);

    bool operator==(const ConstIterator< T >& other) const;
    bool operator!=(const ConstIterator< T >& other) const;

    Node< T >* getNode() const;

  private:
    Node< T >* node_;
  };

  template< typename T >
  ConstIterator< T >::ConstIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  ConstIterator< T >::ConstIterator(const ConstIterator< T >& other):
    node_(other.node_)
  {}

  template< typename T >
  const T& ConstIterator< T >::operator*()
  {
    return node_->data_;
  }

  template< typename T >
  const T* ConstIterator< T >::operator->()
  {
    return &node_->data_;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    ConstIterator< T > temp(*this);
    operator++();
    return temp;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    ConstIterator< T > temp(*this);
    operator--();
    return temp;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator+(size_t pos)
  {
    auto temp(*this);
    for (size_t i = 0; i < pos; i++)
    {
      temp++;
    }
    return temp;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator-(size_t pos)
  {
    auto temp(*this);
    for (size_t i = 0; i < pos; i++)
    {
      temp--;
    }
    return temp;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator[](size_t pos)
  {
    for (size_t i = 0; i < pos; i++)
    {
      operator++();
    }
    return *this;
  }

  template< typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T >& other) const
  {
    return !(node_ == other.node_);
  }

  template< typename T >
  Node< T >* ConstIterator< T >::getNode() const
  {
    return this->node_;
  }

}

#endif
