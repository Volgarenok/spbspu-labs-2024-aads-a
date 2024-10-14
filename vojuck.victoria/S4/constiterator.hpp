#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <iterator>
#include <forward_list>
#include "node.hpp"
#include "iterator.hpp"

namespace vojuck
{
  template < typename T >
  struct ConstIteratorList: public std::iterator< std::forward_iterator_tag, T >
  {
  public:


    ConstIteratorList():
      node_(nullptr)
    {}
    ConstIteratorList(details::Node< T > * node):
      node_(node)
    {}
    ~ConstIteratorList() = default;

    ConstIteratorList(const ConstIteratorList< T > &) = default;
    ConstIteratorList(const IteratorList< T > & other):
      node_(other.node_)
    {}
    ConstIteratorList & operator=(const ConstIteratorList< T > &) = default;
    ConstIteratorList & operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }
    ConstIteratorList operator++(int)
    {
      assert(node_ != nullptr);
      ConstIteratorList result(*this);
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

    bool operator==(const ConstIteratorList< T > &rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const ConstIteratorList< T > &rhs) const
    {
      return !(rhs == *this);
    }
  private:
    details::Node< T > * node_;
  };
}


#endif
