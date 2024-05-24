#ifndef ITERATOR_TREE_HPP
#define ITERATOR_TREE_HPP

#include <functional>
#include <iterator>
#include <utility>
#include "AVLtreeNode.hpp"
#include "constIteratorTree.hpp"

namespace novokhatskiy
{
  template < class Key, class Value, class Compare >
  class Tree;

  template < class Key, class Value, class Compare >
  struct ConstIteratorTree;

  template < class Key, class Value, class Compare = std::less< Key > >
  struct IteratorTree: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    using node_t = detail::NodeTree< Key, Value >;
    using iter = IteratorTree< Key, Value, Compare >;
    using constIter = ConstIteratorTree< Key, Value, Compare >;

    IteratorTree():
      node_(nullptr)
    {}

    bool operator!=(const iter& other) const
    {
      return !(*this == other);
    }

    bool operator==(const iter& other) const
    {
      return node_ == other.node_;
    }

    bool operator==(const constIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const constIter& other) const
    {
      return !(node_ == other.node_);
    }

    std::pair< Key, Value > operator*() const
    {
      return node_->value;
    }

    std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->value);
    }

    iter operator++()
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
        return *this;
      }
      else
      {
        while (node_->parent && node_->parent->right == node_)
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
        return *this;
      }
    }

    iter operator++(int)
    {
      iter tmp(*this);
      ++(*this);
      return tmp;
    }

    iter operator--()
    {
      if (node_->left)
      {
        node_ = node_->left;
        for (; node_->right; node_ = node_->right)
        {}
      }
      else
      {
        for (; node_ == node_->parent->left; node_ = node_->parent)
        {}
        node_ = node_->parent;
      }
      return *this;
    }

    iter operator--(int)
    {
      iter tmp(*this);
      --(*this);
      return tmp;
    }

  private:
    node_t* node_;
    friend class Tree< Key, Value, Compare >;
    friend struct ConstIteratorTree< Key, Value, Compare >;
    explicit IteratorTree(node_t* other):
      node_(other)
    {}
  };
}

#endif
