#ifndef CONST_FORWARD_LIST_ITERATORS
#define CONST_FORWARD_LIST_ITERATORS

#include <iterator>
#include <assert.h>
#include "forward_list_iterators.hpp"

namespace novokhatskiy
{
  template <typename T>
  class ForwardList;

  template <typename T>
  class Node;

  template <typename T>
  class ConstForwardIterator: public std::iterator<std::forward_iterator_tag, T >
  {
    friend class novokhatskiy::ForwardList<T>;
  public:
    using constIter = ConstForwardIterator< T >;
    ConstForwardIterator() :
      node_(nullptr)
    {}
    ConstForwardIterator(Node< T >* node):
      node_(node)
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
    };
    bool operator==(const constIter& other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const constIter& other) const
    {
      return !(node_ == other.node_);
    }

    constIter& moveIterator(size_t size)
    {
      for (size_t i = 0; i != size; i++)
      {
        node_ = node_->next_;
      }
      return *this;
    }
    const T& operator*() const
    {
      return node_.value_;
    }
    const T* operator->() const
    {
      assert(this->node_ != nullptr);
      return std::addressof(this->node_->value_);
    }
    ~ConstForwardIterator() = default;
  private:
    const Node< T >* node_;
  };
}

#endif
