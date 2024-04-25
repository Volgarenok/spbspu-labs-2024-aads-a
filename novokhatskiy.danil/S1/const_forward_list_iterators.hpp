#ifndef CONST_FORWARD_LIST_ITERATORS
#define CONST_FORWARD_LIST_ITERATORS

#include <cassert>
#include <iterator>
#include "forward_list_iterators.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template < typename T >
  class ForwardList;

  template < typename T >
  class ForwardIterator;

  template < typename T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class novokhatskiy::ForwardList< T >;
    friend class novokhatskiy::ForwardIterator< T >;

  public:
    using constIter = ConstForwardIterator< T >;
    ConstForwardIterator():
      node_(nullptr)
    {}
    ConstForwardIterator(const constIter&) = default;
    constIter& operator=(const constIter&) = default;

    constIter& operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    };
    constIter operator++(int)
    {
      assert(node_ != nullptr);
      constIter temp = (*this);
      ++(*this);
      return temp;
    }
    bool operator==(const constIter other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const constIter other) const
    {
      return !(node_ == other.node_);
    }

    bool operator!=(ForwardIterator< T >& other) const
    {
      return node_ != other.node_;
    }
    const T& operator*() const
    {
      return node_->value_;
    }
    const T* operator->() const
    {
      assert(this->node_ != nullptr);
      return std::addressof(this->node_->value_);
    }
    ~ConstForwardIterator() = default;

  private:
    detail::Node< T >* node_;
    ConstForwardIterator(detail::Node< T >* node):
      node_(node)
    {}
  };
}
#endif
