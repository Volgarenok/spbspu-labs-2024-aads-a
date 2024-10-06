#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <cassert>
#include <iterator>
#include <stdexcept>
#include "node.hpp"

namespace petuhov
{
  template < typename T >
  class List;

  template < typename T >
  class ConstIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
    friend class List< T >;

  public:
    ConstIterator() = default;
    ConstIterator(const detail::Node< T > *node) : node_(node) {}
    ConstIterator(const ConstIterator &other) = default;

    ConstIterator& operator=(const ConstIterator &other) = default;

    const T &operator*() const
    {
      return node_->value_;
    }

    const T *operator->() const
    {
      return &(**this);
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
    const detail::Node< T > *node_;
  };
}

#endif
