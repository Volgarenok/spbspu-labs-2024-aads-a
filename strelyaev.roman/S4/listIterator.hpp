#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename T >
  struct Iterator
  {
    public:

    Iterator(Node< T >* node):
      node_(node)
    {}

    T& operator*()
    {
      return node_->value_;
    }

    T* operator->()
    {
      return std::addressof(node_->value_);
    }

    Iterator< T >& operator++()
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        while (node_->left_)
        {
          node_ = node_->left_;
        }
        return *this;
      }
      while(!node_->isRoot() && node_->isRightChild())
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }

    Iterator< T >& operator++(int)
    {
      Iterator< T > result(*this);
      ++(*this);
      return result;
    }

    bool operator==(const Iterator< T > rhs)
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const Iterator< T > rhs)
    {
      return !(*this == rhs);
    }

    private:
      Node< T >* node_;
  };

}

#endif