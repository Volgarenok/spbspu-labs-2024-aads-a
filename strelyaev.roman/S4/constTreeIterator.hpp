#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename T >
  struct ConstIterator
  {
    public:
    ConstIterator(Node< T >* node):
      node_(node)
    {}

    ConstIterator(const ConstIterator< T >& val):
      node_(val.node_)
    {}

    T& operator*()
    {
      return node_->value_;
    }

    T* operator->()
    {
      return std::addressof(node_->value_);
    }

    ConstIterator< T >& operator++()
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

    ConstIterator< T >& operator++(int)
    {
      ConstIterator< T > result(*this);
      ++(*this);
      return result;
    }

    bool operator==(ConstIterator< T > rhs)
    {
      return node_ == rhs.node_;
    }

    bool operator!=(ConstIterator< T > rhs)
    {
      return !(*this == rhs);
    }

    private:
      Node< T >* node_;
  };

}

#endif
