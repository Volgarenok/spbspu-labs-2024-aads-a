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
  struct IteratorList: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
  public:
    using this_t = IteratorList< T >;

    IteratorList():
      node_(nullptr)
    {}
    ~IteratorList() = default;
    IteratorList(const this_t &) = default;
    IteratorList(details::Node< T > * node):
        node_(node)
    {}
    this_t & operator=(const this_t &) = default;
    this_t & operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }
    this_t operator++(int)
    {
      assert(node_ != nullptr);
      this_t result(*this);
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

    bool operator==(const this_t &rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const this_t &rhs) const
    {
      return !(rhs == *this);
    }
  private:
    details::Node< T > * node_;
  };
}

#endif
