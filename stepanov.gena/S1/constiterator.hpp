#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <iterator>
#include <cassert>
#include "node.hpp"

namespace stepanov
{
  template < typename T >
  class List;

  template < typename T >
  class Iterator;

  template < typename T >
  class ConstIterator: std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
    friend class Iterator< T >;

  public:
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using this_type = ConstIterator< T >;
    ConstIterator():
      node_(nullptr)
    {}
    ConstIterator(Node< T > * node):
      node_(node)
    {}
    ~ConstIterator() = default;
    ConstIterator(const this_type &) = default;
    ConstIterator(const Iterator< T > & other):
      node_(other.node_)
    {}
    this_type & operator=(const this_type &) = default;
    this_type & operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }
    this_type operator++(int)
    {
      assert(node_ != nullptr);
      this_type result(*this);
      ++(*this);
      return result;
    }
    const T & operator*() const
    {
      assert(node_ != nullptr);
      return node_->data_;
    }
    const T * operator->() const
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }

    bool operator==(const this_type & rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const this_type & rhs) const
    {
      return !(rhs == *this);
    }

  private:
    Node< T > * node_;
  };
}

#endif
