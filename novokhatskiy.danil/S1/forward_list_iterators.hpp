#ifndef FORWARD_LIST_ITERATORS_HPP
#define FORWARD_LIST_ITERATORS_HPP
#include <cassert>
#include "const_forward_list_iterators.hpp"
#include "forward_list.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template < typename T >
  class ForwardList;

  template < typename T >
  class ConstForwardIterator;

  template < typename T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class novokhatskiy::ForwardList< T >;
    friend class novokhatskiy::ConstForwardIterator< T >;

  public:
    using iter = ForwardIterator< T >;
    ForwardIterator():
      node_(nullptr)
    {}
    ForwardIterator(const iter&) = default;
    iter& operator=(const iter&) = default;

    iter& operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    };
    iter operator++(int)
    {
      assert(node_ != nullptr);
      iter temp = (*this);
      node_ = node_->next_;
      return temp;
    }
    bool operator==(const iter other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const iter other) const
    {
      return !(node_ == other.node_);
    }

    bool operator!=(ConstForwardIterator< T > constIt) const
    {
      return !(node_ == constIt.node_);
    }

    T& operator*()
    {
      assert(node_ != nullptr);
      return node_->value_;
    }
    const T& operator*() const
    {
      return node_->value_;
    }
    T* operator->()
    {
      assert(this->node_ != nullptr);
      return std::addressof(this->node_->value_);
    }
    const T* operator->() const
    {
      assert(this->node_ != nullptr);
      return std::addressof(this->node_.value_);
    }
    ~ForwardIterator() = default;

  private:
    detail::Node< T >* node_;
    explicit ForwardIterator(detail::Node< T >* node):
      node_(node)
    {}
  };
}

#endif
