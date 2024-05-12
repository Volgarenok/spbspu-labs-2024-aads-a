#ifndef ITERATOR_TREE_HPP
#define ITERATOR_TREE_HPP

#include <cassert>
#include <iterator>
#include <functional>
#include <utility>
#include "AVLtreeNode.hpp"
#include "constIteratorTree.hpp"

namespace novokhatskiy
{
  template< class Key, class Value, class Compare >
  class Tree;

  template< class Key, class Value, class Compare >
  struct ConstIteratorTree;

  template< class Key, class Value, class Compare = std::less< Key > >
  struct IteratorTree: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    using node_t = detail::NodeTree< Key, Value >;
    using iter = IteratorTree< Key, Value, Compare >;
    using constIter = ConstIteratorTree< Key, Value, Compare >;

    IteratorTree(node_t* other) :
      node_(other)
    {}

    bool operator!=(const iter& other) const
    {
      assert(node_ != nullptr);
      return !(*this == other);
    }

    bool operator==(const iter& other) const
    {
      assert(node_ != nullptr);
      return node_ == other.node_;
    }

    bool operator==(const constIter& other) const
    {
      assert(node_ != nullptr);
      return node_ == other.node_;
    }

    bool operator!=(const constIter& other) const
    {
      assert(node_ != nullptr);
      return !(node_ == other.node_);
    }

    std::pair< Key, Value > operator*() const
    {
      assert(node_ != nullptr);
      return node_->value;
    }

    std::pair< Key, Value >* operator->() const
    {
      assert(node_ != nullptr);
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
        //goLastLeft();
        return *this;
      }
      while (node_->parent && node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }

    iter operator++(int)
    {
      iter tmp(*this);
      ++(*this);
      return tmp;
    }

    iter operator--()
    {
      node_ = predecessor(node_);
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

    void goLastRight(node_t* tmp)
    {
      //auto tmp = node_->right;
      while (tmp->right)
      {
        tmp = tmp->right;
      }
      //node_ = tmp;
    }

    void goLastLeft()
    {
      /*while (other->left)
      {
        other = other->left;
      }*/
      auto tmp = node_->left;
      while (tmp->left)
      {
        tmp = tmp->left;
      }
      node_ = tmp;
    }

    node_t* predecessor(node_t* node)
    {
      if (node->left)
      {
        goLastRight(node->left);
      }
      node_t* tmp = node->parent;
      while (tmp && node == tmp->left)
      {
        node = tmp;
        tmp = tmp->parent;
      }
      return tmp;
    }
  };
}

#endif
