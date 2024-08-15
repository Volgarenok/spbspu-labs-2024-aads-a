#ifndef CONST_TREE_ITERATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include "treeNode.hpp"
#include "treeIterator.hpp"

namespace marishin
{
  template< class Key, class Value, class Compare >
  class Tree;

  template< class Key, class Value, class Compare >
  class IteratorTree;

  template< class Key, class Value, class Compare >
  class ConstIteratorTree
  {
    friend class Tree< Key, Value, Compare >;
    friend class IteratorTree< Key, Value, Compare >;
    using pair_key_t = std::pair< Key, Value >;
    using node_t = detail::TreeNode< Key, Value >;
    using const_iterator = ConstIteratorTree< Key, Value, Compare >;
    using iterator = IteratorTree< Key, Value, Compare >;
  public:
    ConstIteratorTree():
      node_(nullptr)
    {}
    ConstIteratorTree(const const_iterator &) = default;
    const_iterator & operator=(const const_iterator &) = default;
    ConstIteratorTree(const_iterator && other) noexcept = default;
    const_iterator & operator=(const_iterator && other) noexcept = default;
    const_iterator & operator++()
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
        while ((node_->parent) && (node_->parent->right == node_))
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
        return *this;
      }
    }
    const_iterator operator++(int)
    {
      const_iterator temp(*this);
      ++(*this);
      return temp;

    }

    const_iterator & operator--()
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
      else
      {
        while ((node_->parent) && (node_->parent->left == node_))
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
        return *this;
      }
    }
    const_iterator operator--(int)
    {
      const_iterator temp(*this);
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator & other) const
    {
      return (node_ == other.node_);
    }
    bool operator==(iterator & other) const
    {
      return (node_ == other.node_);
    }
    bool operator!=(const const_iterator & other) const
    {
      return node_ != other.node_;
    }
    bool operator!=(iterator & other) const
    {
      return node_ != other.node_;
    }
    const pair_key_t & operator*() const
    {
      return node_->data;
    }
    const pair_key_t * operator->() const
    {
      return std::addressof(node_->data);
    }
    ~ConstIteratorTree() = default;
  private:
    const node_t * node_;
    explicit ConstIteratorTree(node_t * node):
      node_(node)
    {}
  };
}

#endif
