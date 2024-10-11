#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <stddef.h>
#include <memory>

#include "node.hpp"

namespace kovtun
{
  template<typename T>
  class ConstIterator
  {
  public:
    using this_t = ConstIterator<T>;

    ConstIterator() :
        node_(nullptr)
    {};

    ~ConstIterator() = default;

    ConstIterator(const this_t &) = default;

    this_t &operator=(const this_t &) = default;

    this_t &operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next;
      return *this;
    };

    this_t &operator++(int)
    {
      assert(node_ != nullptr);
      this_t result(*this);
      ++(*this);
      return result;
    }

    bool operator==(const this_t &rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const this_t &rhs) const
    {
      return !(rhs == *this);
    }

    T &operator*() const
    {
      return node_->val;
    }

    T *operator->() const
    {
      return std::addressof(node_->val);
    }

    this_t &operator--()
    {
      node_ = node_->prev;
      return node_;
    }

    this_t &operator--(int)
    {
      this_t result(*this);
      --(*this);
      return result;
    }

  private:
    Node<T> *node_;
  };

}

#endif
