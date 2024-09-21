#ifndef ITERATOR_HPP
#define ITERATOR_HPP

 //#include <iterator>
#include <cassert>
#include "node.hpp"
namespace vojuck
{
  template < typename T >
  struct IteratorList
  {
  public:
    List< T > * node;
    using this_t = IteratorLits< T >;

    IteratorList():
      node(nullptr)
    {}
    ~IteratorList() = default;
    IteratorList(const this_t &) = default;
    this_t & operator(const this_t &) = default;

    this_t & operator++();
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
    Node< T > * node_;
  };
}

#endif
