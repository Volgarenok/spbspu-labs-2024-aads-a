#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <iostream>
#include "node.hpp"

namespace sivkov
{
  template < typename T >
  class ConstIterator
  {
  public:
    ConstIterator() :
      node_(nullptr)
    {}
    ConstIterator(Node<T>* node) :
      node_(node)
    {}

    ConstIterator<T>& operator=(const ConstIterator<T>&) = default;
    ConstIterator(const ConstIterator<T>&) = default;
    ~ConstIterator() = default;

    T& operator*();
    T* operator->();

    bool operator!=(const ConstIterator<T>& other) const;
    bool operator==(const ConstIterator<T>& other) const;
    const T& operator*() const;
    const T* operator->() const;
    void advance(size_t n);
    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);

  private:
    Node<T>* node_;
  };

  template< typename T >
  T& ConstIterator<T>::operator*()
  {
    return node_->data;
  }

  template< typename T >
  T* ConstIterator<T>::operator->()
  {
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ConstIterator<T>::operator!=(const ConstIterator<T>& other) const
  {
    return !(node_ == other.node_);
  }

  template< typename T >
  bool ConstIterator<T>::operator==(const ConstIterator<T>& other) const
  {
    return (node_ == other.node_);
  }

  template< typename T >
  const T& ConstIterator<T>::operator*() const
  {
    return node_->data;
  }

  template< typename T >
  const T* ConstIterator<T>::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< typename T >
  void ConstIterator<T>::advance(size_t n)
  {
    for (size_t i = 0; i < n; ++i)
    {
      if (node_ == nullptr)
      {
        return;
      }
      node_ = node_->next;
    }
  }

  template< typename T >
  ConstIterator<T>& ConstIterator<T>::operator++()
  {
    node_ = node_->next;
    return *this;
 }

  template< typename T >
  ConstIterator<T> ConstIterator<T>::operator++(int)
  {
    ConstIterator<T> result(*this);
    ++(*this);
    return result;
  }
}
#endif
