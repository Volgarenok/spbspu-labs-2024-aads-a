#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "node.hpp"

namespace nikitov
{
  template< typename T >
  class Node;

  template< typename T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Node< T >;
  public:
    ListIterator(Node< T >* node):
      node_(node)
    {}
    ListIterator(const ListIterator&) = default;
    ~ListIterator() = default;

    ListIterator& operator=(const ListIterator&) = default;
    ListIterator& operator++()
    {
      node_ = node_->next_;
      return *this;
    }
    ListIterator operator++(int)
    {
      ListIterator temp(*this);
      node_ = node_->next_;
      return temp;
    }
    ListIterator& operator--()
    {
      node_ = node_->prev_;
      return *this;
    }
    ListIterator operator--(int)
    {
      ListIterator temp(*this);
      node_ = node_->prev_;
      return temp;
    }

    T& operator*()
    {
      return node_->value_;
    }
    T* operator->()
    {
      return std::addressof(node_.value_);
    }

    const T& operator*() const
    {
      return node_.value;
    }
    const T* operator->() const
    {
      return std::addressof(node_.value);
    }

    bool operator==(const ListIterator& other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const ListIterator& other) const
    {
      return node_ != other.node_;
    }

  private:
    Node< T >* node_;
  };
}
#endif
