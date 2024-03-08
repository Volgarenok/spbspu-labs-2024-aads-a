#ifndef CONST_ITERATORS_HPP
#define CONST_ITERATORS_HPP

#include <iterator>
#include "iterators.hpp"

namespace namestnikov
{
  template <class T>
  class ConstForwardIterator: public std::iterator<std::forward_iterator_tag, T>
  {
    using const_it_t = ConstForwardIterator<T>;
    using node_t = Node<T>;
  public:
    ConstForwardIterator():
      node_(nullptr)
    {}
    ConstForwardIterator(node_t * node):
      node_(node)
    {}
    ConstForwardIterator(const const_it_t &) = default;
    const_it_t & operator=(const const_it_t &) = default;
    const_it_t & operator++()
    {
      node_ = node_->next_;
      return *this;
    }
    const_it_t operator++(int)
    {
      const_it_t temp(*this);
      ++(*this);
      return temp;
    }
    bool operator!=(const const_it_t & other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const const_it_t & other) const
    {
      return node_ == other.node_;
    }
    const T & operator*() const
    {
      return node_->data_;
    }
    const T * operator->() const
    {
      return std::addressof(node_->data_);
    }
    const_it_t & advance(size_t n)
    {
      for (size_t i = 0; i < n; ++i)
      {
        node_ = node_->next_;
      }
      return *this;
    }
    ~ConstForwardIterator() = default;
  private:
    const node_t * node_;
  };
}

#endif
