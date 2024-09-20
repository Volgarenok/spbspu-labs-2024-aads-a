#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>
#include <cassert>
#include <tree_node.hpp>
#include <const_tree_iterator.hpp>

namespace namestnikov
{
  template< class Key, class Value, class Compare >
  class Tree;

  template< class Key, class Value, class Compare >
  class ConstIteratorTree;

  template< class Key, class Value, class Compare >
  class IteratorTree: public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    friend class Tree< Key, Value, Compare >;
    friend class ConstIteratorTree< Key, Value, Compare >;
    using pair_key_t = std::pair< Key, Value >;
    using node_t = detail::TreeNode< Key, Value >;
    using iterator = IteratorTree< Key, Value, Compare >;
    using const_iterator = ConstIteratorTree< Key, Value, Compare >;
  public:
    IteratorTree():
      node_(nullptr)
    {}
    IteratorTree(const iterator &) = default;
    iterator & operator=(const iterator &) = default;
    IteratorTree(iterator && other) noexcept = default;
    iterator & operator=(iterator && other) noexcept = default;
    iterator & operator++()
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
    iterator operator++(int)
    {
      iterator temp(*this);
      ++(*this);
      return temp;

    }
    iterator & operator--()
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
        while (node_->isLeftChild())
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
        return *this;
      }
    }
    iterator operator--(int)
    {
      iterator temp(*this);
      --(*this);
      return temp;
    }
    bool operator==(const iterator & other) const
    {
      return (node_ == other.node_);
    }
    bool operator==(const_iterator & other) const
    {
      return (node_ == other.node_);
    }
    bool operator!=(const iterator & other) const
    {
      return node_ != other.node_;
    }
    bool operator!=(const_iterator & other) const
    {
      return node_ != other.node_;
    }
    pair_key_t & operator*()
    {
      return node_->data;
    }
    const pair_key_t & operator*() const
    {
      return node_->data;
    }
    pair_key_t * operator->()
    {
      return std::addressof(node_->data);
    }
    const pair_key_t * operator->() const
    {
      return std::addressof(node_->data);
    }
    ~IteratorTree() = default;
  private:
    node_t * node_;
    explicit IteratorTree(node_t * node):
      node_(node)
    {}
  };
}

#endif
