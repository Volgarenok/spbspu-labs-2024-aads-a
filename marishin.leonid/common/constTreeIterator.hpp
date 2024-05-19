#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP

#include <functional>
#include <iterator>
#include <utility>
#include <treeNode.hpp>

namespace marishin
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree:

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  struct ConstIteratorTree
  {
    friend class BinarySearchTree< Key, Value, std::less< Key > >;
    using TreeNode = detail::TreeNode< Key, Value >;

    ConstIteratorTree() = default;
    ConstIteratorTree< Key, Value, Compare >& operator=(const ConstIteratorTree< Key, Value, Compare >&) = default;

    template< typename Key, typename Value, typename Compare >
    ConstIteratorTree(detail::TreeNode< Key, Value >* node):
      node_(node)
    {}

    template< typename Key, typename Value, typename Compare >
    const std::pair< Key, Value >& operator*() const
    {
      return node_->data;
    }

    template< typename Key, typename Value, typename Compare >
    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->data);
    }

    template< typename Key, typename Value, typename Compare >
    ConstIteratorTree< Key, Value, Compare >& operator++()
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
      while (node_->parent && node_->parent->right == node_)
      {
        node_ = node_->parent;
      }
      node_ = node_->parent;
      return *this;
    }

    template< typename Key, typename Value, typename Compare >
    ConstIteratorTree< Key, Value, Compare >& operator++(int)
    {
      ConstIteratorTree< Key, Value > result(*this);
      ++(*this);
      return result;
    }

    template< typename Key, typename Value, typename Compare >
    bool operator==(const ConstIteratorTree< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }

    template < typename Key, typename Value, typename Compare >
    bool operator!=(const ConstIteratorTree< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }

    private:
      detail::TreeNode< Key, Value >* node_;

      ConstIterator(detail::TreeNode< Key, Value >* node):
        node_(node)
      {}
  };
}
