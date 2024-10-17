#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <iterator>
#include <forward_list>
#include "node.hpp"
#include "list.hpp"

namespace vojuck
{
  template < typename T >
  class List;
  template < typename T >
  struct IteratorList
  {
    friend class List< T >;
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    IteratorList():
      node_(nullptr)
    {}
    ~IteratorList() = default;
    IteratorList(const IteratorList &) = default;
    IteratorList(details::Node< T > * node):
        node_(node)
    {}
    IteratorList & operator=(const IteratorList &) = default;
    IteratorList & operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }
    IteratorList operator++(int)
    {
      assert(node_ != nullptr);
      IteratorList result(*this);
      ++(*this);
      return result;
    }

    T * operator->()
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }
    T & operator*()
    {
      assert(node_ != nullptr);
      return node_->data_;
    }

    bool operator==(const IteratorList &rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const IteratorList &rhs) const
    {
      return !(rhs == *this);
    }
  private:
    details::Node< T > * node_;
  };
}

#endif
