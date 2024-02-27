#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <cassert>
#include "node.hpp"

namespace namestnikov
{
  template <class T>
  struct ForwardIterator:
    public std::iterator<std::forward_iterator_tag, T>
  {
    using this_t = ForwardIterator<T>;
    ForwardIterator(): node_(nullptr) {}
    ForwardIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++()
    {
      assert(node != nullptr);
      node_ = node_->next;
      return *this;
    }
    this_t operator++(int)
    {
      assert(node_ != nullptr);
      this_t result(*this);
      ++(*this);
      return result;
    }
    bool operator!=(const this_t & other) const
    {
      return node_ == other.node_;
    }
    bool operator==(const this_t & other) const
    {
      return !(other == *this);
    }
    T & operator*()
    {
      assert(node_ != nullptr);
      return node_->data_;
    }
    const T & operator*() const
    {
      assert(node_ != nullptr);
      return node_->data_;
    }
    T * operator->()
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }
    const T * operator->() const
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }
    ~ForwardIterator() = default;
    Node<T> * node_;
  };
}
#endif
