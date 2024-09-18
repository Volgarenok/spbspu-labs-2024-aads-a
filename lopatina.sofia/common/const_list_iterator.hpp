#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <forward_list>
#include <cassert>
#include "node.hpp"

namespace lopatina
{
  template < typename T >
  class List;

  template < typename T >
  struct ListIterator;

  template < typename T >
  struct ConstListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
    friend struct ListIterator< T >;

  public:
    using this_t = ConstListIterator< T >;
    ConstListIterator():
      node_(nullptr)
    {}
    ConstListIterator(Node< T > * node):
      node_(node)
    {}
    ~ConstListIterator() = default;

    ConstListIterator(const this_t &) = default;
    ConstListIterator(const ListIterator< T > & other):
      node_(other.node_)
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

    bool operator==(const this_t & rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const this_t & rhs) const
    {
      return !(rhs == *this);
    }

  private:
    Node< T > * node_;
  };
}

#endif
