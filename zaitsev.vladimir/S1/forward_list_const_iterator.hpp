#ifndef CONST_FORWARD_LIST_ITERATOR_HPP
#define CONST_FORWARD_LIST_ITERATOR_HPP
#include <stdexcept>
#include <iterator>
#include "node.hpp"

namespace zaitsev
{
  template< typename T >
  class ConstForwardListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ConstForwardListIterator();
    ConstForwardListIterator(Node< T >* node);
    ConstForwardListIterator(const ConstForwardListIterator< T >&) = default;
    ~ConstForwardListIterator() = default;
    ConstForwardListIterator< T >& operator=(const ConstForwardListIterator< T >&) = default;
    ConstForwardListIterator< T >& operator++();
    ConstForwardListIterator< T > operator++(int);
    const T& operator*() const;
    const T* operator->() const;
    bool operator!=(const ConstForwardListIterator< T >& other) const;
    bool operator==(const ConstForwardListIterator< T >& other) const;
  private:
    Node< T >* node_;
  };

  template<typename T>
  ConstForwardListIterator<T>::ConstForwardListIterator():
    node_(nullptr)
  {}

  template<typename T>
  ConstForwardListIterator<T>::ConstForwardListIterator(Node<T>* node):
    node_(node)
  {}

  template< typename T >
  ConstForwardListIterator< T >& ConstForwardListIterator< T >::operator++()
  {
    if (!node_)
    {
      throw std::out_of_range("Iterator is out of range");
    }
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ConstForwardListIterator< T > ConstForwardListIterator< T >::operator++(int)
  {
    ConstForwardListIterator< T > res = *this;
    if (!node_)
    {
      throw std::out_of_range("Iterator is out of range");
    }
    ++(*this);
    return res;
  }

  template<typename T>
  const T& ConstForwardListIterator<T>::operator*() const
  {
    if (!node_)
    {
      throw std::out_of_range("Iterator is out of range");
    }
    return this->node_->value_;
  }

  template<typename T>
  const T* ConstForwardListIterator<T>::operator->() const 
  {
    if (!node_)
    {
      throw std::out_of_range("Iterator is out of range");
    }
    return std::addressof(this->node_->value_);
  }

  template< typename T >
  bool ConstForwardListIterator< T >::operator!=(const ConstForwardListIterator<T>& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  bool ConstForwardListIterator< T >::operator==(const ConstForwardListIterator< T >& other) const
  {
    return node_ == other.node_;
  }
}
#endif
