#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP

#include <functional>
#include <iterator>
#include <utility>
#include <treeNode.hpp>
#include <treeIterator.hpp>

namespace marishin
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree;

  template< typename Key, typename Value, typename Compare >
  class IteratorTree;

  template< typename Key, typename Value, typename Compare >
  class ConstIteratorTree
  {
    friend class BinarySearchTree< Key, Value, Compare >;
    friend class IteratorTree< Key, Value, Compare >
    using TreeNode = detail::TreeNode< Key, Value >;
  public:

    ConstIteratorTree(const ConstIteratorTree< Key, Value, Compare >&) = default;
    ConstIteratorTree< Key, Value, Compare >& operator=(const ConstIteratorTree< Key, Value, Compare >&) = default;
    ConstIteratorTree(ConstIteratorTree< Key, Value, Compare >&& other) noexcept = default;
    ConstIteratorTree< Key, Value, Compare >& operator=(ConstIteratorTree< Key, Value, Compare >&& other) noexcept = default;
    ConstIteratorTree< Key, Value, Compare >&

    ConstIteratorTree():
      node_(nullptr)
    {}

    const std::pair< Key, Value >& operator*() const
    {
      return node_->data;
    }

    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->data);
    }

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

    ConstIteratorTree< Key, Value, Compare >& operator++(int)
    {
      ConstIteratorTree< Key, Value > result(*this);
      ++(*this);
      return result;
    }

    bool operator==(const ConstIteratorTree< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator==(IteratorTree< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const ConstIteratorTree< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }

    bool operator!=(IteratorTree< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }

    ~ConstIteratorTree() = default;
    private:
      detail::TreeNode< Key, Value >* node_;

      ConstIteratorTree(detail::TreeNode< Key, Value >* node):
        node_(node)
      {}
  };
}

#endif
