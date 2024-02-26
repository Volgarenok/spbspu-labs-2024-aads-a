#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <cassert>
#include "node.hpp"

namespace namestnikov
{
  template <class T>
  struct ForwardIterator:
    public std::forward_iterator_tag
  {
    using this_t = ForwardIterator<T>;
    ForwardIterator(): node(nullptr) {}
    ForwardIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++()
    {
      assert(node != nullptr);
      node = node->next;
      return *this;
    }
    this_t operator++(int)
    {
      assert(node != nullptr);
      this_t result(*this);
      ++(*this);
      return result;
    }
    bool operator!=(const this_t & other) const
    {
      return node == other.node;
    }
    bool operator==(const this_t & other) const
    {
      return !(other == *this);
    }
    T & operator*()
    {
      assert(node != nullptr);
      return node->data_;
    }
    const T & operator*() const
    {
      assert(node != nullptr);
      return node->data_;
    }
    T * operator->()
    {
      assert(node != nullptr);
      return std::addressof(node->data_);
    }
    const T * operator->() const
    {
      assert(node != nullptr);
      return std::addressof(node->data_);
    }
    ~ForwardIterator() = default;
    Node<T> * node;
  };
}
#endif
