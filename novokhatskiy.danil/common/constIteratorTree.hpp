#ifndef CONST_ITERATOR_TREE
#define CONST_ITERATOR_TREE

#include <functional>
#include <iterator>
#include <utility>
#include <AVLtreeNode.hpp>
#include <IteratorTree.hpp>

namespace novokhatskiy
{
  template < class Key, class Value, class Compare >
  struct IteratorTree;

  template < class Key, class Value, class Compare >
  class Tree;

  template < class Key, class Value, class Compare = std::less< Key > >
  struct ConstIteratorTree: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    using node_t = detail::NodeTree< Key, Value >;
    using constIter = ConstIteratorTree< Key, Value, Compare >;
    using iter = IteratorTree< Key, Value, Compare >;

    ConstIteratorTree():
      node_(nullptr)
    {}

    constIter& operator=(const constIter& other) = default;

    bool operator!=(const constIter& other) const
    {
      return !(*this == other);
    }

    bool operator==(const constIter& other) const
    {
      return node_ == other.node_;
    }

    constIter operator++()
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

    constIter operator++(int)
    {
      constIter tmp(*this);
      ++(*this);
      return tmp;
    }

    constIter operator--()
    {
      if (node_->left)
      {
        node_ = node_->left;
        while (node_->right)
        {
          node_ = node_->right;
        }
        return *this;
      }
      while (node_->parent && node_->parent->left == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }

    constIter operator--(int)
    {
      constIter tmp(*this);
      --(*this);
      return tmp;
    }

    const std::pair< Key, Value > operator*() const
    {
      return node_->value;
    }

    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->value);
    }

    bool operator==(const iter it) const
    {
      return node_ == it.node_;
    }

    bool operator!=(const iter it) const
    {
      return node_ != it.node_;
    }

  private:
    node_t* node_;
    friend class Tree< Key, Value, Compare >;
    friend struct IteratorTree< Key, Value, Compare >;

    explicit ConstIteratorTree(node_t* node):
      node_(node)
    {}
  };
}

#endif
