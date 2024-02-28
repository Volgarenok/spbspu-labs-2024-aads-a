#ifndef FORWARD_LIST_ITERATORS_HPP
#define FORWARD_LIST_ITERATORS_HPP
#include "forward_list.hpp"
#include "node.hpp"
#include<assert.h>

namespace novokhatskiy
{
  template <typename T>
  class ForwardList;

  template <typename T>
  class Node;

  template <typename T>
  class ForwardIterator : public std::iterator<std::forward_iterator_tag, T > 
  {
    friend class novokhatskiy::ForwardList<T>;
  public:
    using iter = ForwardIterator<T>;
    ForwardIterator() :
      node_(nullptr)
    {}
    ForwardIterator(Node< T >* node):
      node_(node)
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
      ++(*this);
      return temp;
    };
    bool operator==(const iter& other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const iter& other) const
    {
      return !(node_ == other.node_);
    }
    T& operator*()
    {
      assert(node_ != nullptr);
      return node_->value_;
    }
    const T& operator*() const
    {
      return node_.value_;
    }
    T* operator->() 
    {
      assert(this->node_ != nullptr);
      return std::addressof(this->node_.value_);
    }
    const T* operator->() const
    {
      assert(this->node_ != nullptr);
      return std::addressof(this->node_.value_);
    }
    ~ForwardIterator() = default;
  private:
    Node< T >* node_;
  };
}
#endif
