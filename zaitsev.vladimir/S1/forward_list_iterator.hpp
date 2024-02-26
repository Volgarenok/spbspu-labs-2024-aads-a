#ifndef FORWARD_LIST_ITERATOR_HPP
#define FORWARD_LIST_ITERATOR_HPP
#include <stdexcept>
#include "node.hpp"

namespace zaitsev
{
  template< typename T >
  class ForwardListIterator {
  public:
    ForwardListIterator();
    ForwardListIterator(Node< T >* node);
    ForwardListIterator(const ForwardListIterator< T >&) = default;
    ~ForwardListIterator() = default;
    ForwardListIterator< T >& operator=(const ForwardListIterator< T >&) = default;
    ForwardListIterator< T >& operator++();
    ForwardListIterator< T > operator++(int);
    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;
    bool operator!=(const ForwardListIterator< T >& other) const;
    bool operator==(const ForwardListIterator< T >& other) const;
  private:
    Node< T >* node_;
  };

  template<typename T>
  ForwardListIterator<T>::ForwardListIterator():
    node_(nullptr)
  {}

  template<typename T>
  ForwardListIterator<T>::ForwardListIterator(Node<T>*node)
    :node_(node)
  {}

  template< typename T >
  ForwardListIterator< T >& ForwardListIterator< T >::operator++()
  {
    if (!node_)
    {
      throw std::runtime_error("Iterator is out of range");
    }
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    ForwardListIterator< T > = *this;
    if (!node_)
    {
      throw std::runtime_error("Iterator is out of range");
    }
    return ForwardListIterator<T>();
  }

  template<typename T>
  T& ForwardListIterator<T>::operator*()
  {
    return this->node_->value_;
  }

  template<typename T>
  T* ForwardListIterator<T>::operator->()
  {
    return std::addressof(this->node_->value_);
  }

  template<typename T>
  const T& ForwardListIterator<T>::operator*() const
  {
    return this->node_->value_;
  }

  template<typename T>
  const T* ForwardListIterator<T>::operator->() const
  {
    return this->node_->value_;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const ForwardListIterator<T>& other) const
  {
    return node_ !=other.node_;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator==(const ForwardListIterator< T >& other) const
  {
    return node_ == other.node_;
  }
}
#endif
