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
  struct ConstListIterator;

  template < typename T >
  struct ListIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
    friend struct ConstListIterator< T >;

  public:
    using this_t = ListIterator< T >;
    ListIterator():
      node_(nullptr)
    {}
    ListIterator(Node< T > * node):
      node_(node)
    {}
    ~ListIterator() = default;

    ListIterator(const this_t &) = default;
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
    T & operator*()
    {
      assert(node_ != nullptr);
      return node_->data_;
    }
    T * operator->()
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
