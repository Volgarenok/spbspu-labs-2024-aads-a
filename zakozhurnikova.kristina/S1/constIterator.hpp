#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP
#include "node.hpp"
#include <memory>

namespace zakozhurnikova
{
  template < typename T >
  struct ConstIterator
  {
    using this_t = ConstIterator< T >;
    ConstIterator();
    ConstIterator(Node< T >* node);
    ConstIterator(const this_t&) = default;
    ~ConstIterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    this_t& operator--();
    this_t operator--(int);
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;
    const T& operator*() const;
    const T* operator->() const;

    this_t operator+(size_t);
    this_t operator-(size_t);

  private:
    Node< T >* node_;
  };

  template < typename T >
  ConstIterator< T > ConstIterator< T >::operator+(size_t k)
  {
    ConstIterator< T > result(*this);
    for (size_t i = 0; i < k; ++i)
    {
      ++result;
    }
    return result;
  }

  template < typename T >
  ConstIterator< T > ConstIterator< T >::operator-(size_t k)
  {
    ConstIterator< T > result(*this);
    for (size_t i = 0; i < k; ++i)
    {
      --result;
    }
    return result;
  }

  template < typename T >
  ConstIterator<T>::ConstIterator() :
    node_(nullptr)
  {}

  template < typename T >
  ConstIterator< T >::ConstIterator(Node< T >* node) :
    node_(node)
  {}

  template < typename T >
  ConstIterator< T >& ConstIterator< T >::operator++()
  {
    node_ = node_->next;
    return *this;
  }

  template < typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int rhs)
  {
    ConstIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  ConstIterator< T >& ConstIterator< T >::operator--()
  {
    node_ = node_->prev;
    return *this;
  }


  template < typename T >
  ConstIterator< T > ConstIterator< T >::operator--(int rhs)
  {
    ConstIterator< T > result(*this);
    --(*this);
    return result;
  }

  template < typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T >& rhs) const
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T >& rhs) const
  {
    return !(*this == rhs);
  }


  template < typename T >
  const T& ConstIterator< T >::operator*() const
  {
    return node_->data;
  }

  template < typename T >
  const T* ConstIterator< T >::operator->() const
  {
    return std::addressof(node_->data);
  }
}

#endif
