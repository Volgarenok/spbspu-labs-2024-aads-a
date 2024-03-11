#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator>
#include "node.hpp"
#include "const_iterators.hpp"

namespace namestnikov
{
  template <class T>
  class ForwardList;

  template <class T>
  class Node;

  template <class T>
  class ConstForwardIterator;

  template <class T>
  class ForwardIterator: public std::iterator<std::forward_iterator_tag, T>
  {
    friend class namestnikov::ForwardList<T>;
    friend class namestnikov::ConstForwardIterator<T>;
    using iterator_t = ForwardIterator<T>;
    using const_it_t = ConstForwardIterator<T>;
    using node_t = Node<T>;
  public:
    ForwardIterator() :
      node_(nullptr)
    {}
    ForwardIterator(node_t * node):
      node_(node)
    {}
    ForwardIterator(const iterator_t &) = default;
    iterator_t & operator=(const iterator_t &) = default;
    ForwardIterator(ForwardIterator && other) noexcept:
      node_(other.node_)
    {
      other.node_ = nullptr;
    }
    iterator_t & operator++()
    {
      node_ = node_->next_;
      return *this;
    }
    iterator_t operator++(int)
    {
      iterator_t temp(*this);
      ++(*this);
      return temp;
    }
    bool operator!=(const iterator_t & other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const iterator_t & other) const
    {
      return (node_ == other.node_);
    }
    bool operator!=(const_it_t & other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const_it_t & other) const
    {
      return (node_ == other.node_);
    }
    T & operator*()
    {
      return node_->data_;
    }
    const T & operator*() const
    {
      return node_->data_;
    }
    T * operator->()
    {
      return std::addressof(node_->data_);
    }
    const T * operator->() const
    {
      return std::addressof(node_->data_);
    }
    iterator_t & advance(size_t n)
    {
      for (size_t i = 0; i < n; ++i)
      {
        node_ = node_->next_;
      }
      return *this;
    }
    ~ForwardIterator() = default;
  private:
    node_t * node_;
  };
}
#endif
