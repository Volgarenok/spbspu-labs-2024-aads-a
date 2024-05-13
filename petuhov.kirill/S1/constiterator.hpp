#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <cassert>
#include "node.hpp"

namespace petuhov
{
  template < typename T >
  class List;

  template < typename T >
  class ConstIterator
  {
    friend class List< T >;

  public:
    ConstIterator() : node_(nullptr) {}
    ConstIterator(const Node< T > *node) : node_(node) {}
    ConstIterator(const ConstIterator &other) = default;

    const T &operator*() const
    {
      assert(node_ != nullptr);
      return node_->value_;
    }

    const T *operator->() const
    {
      return &(operator*());
    }

    ConstIterator &operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }

    ConstIterator operator++(int)
    {
      assert(node_ != nullptr);
      ConstIterator temp = *this;
      node_ = node_->next_;
      return temp;
    }

    bool operator==(const ConstIterator &other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const ConstIterator &other) const
    {
      return node_ != other.node_;
    }

  private:
    const Node< T > *node_;
  };
}

#endif
