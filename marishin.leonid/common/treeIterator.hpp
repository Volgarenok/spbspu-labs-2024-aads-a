#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP

#include <functional>
#include <iterator>
#include <utility>
#include <treeNode.hpp>
#include <constTreeIterator.hpp>

namespace marishin
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree;

  template< typename Key, typename Value, typename Compare >
  class ConstIteratorTree;

  template< typename Key, typename Value, typename Compare >
  class IteratorTree
  {
    friend class BinarySearchTree< Key, Value, Compare >;
    friend class ConstIteratorTree< Key, Value, Compare >;
    using TreeNode = detail::TreeNode< Key, Value >;
  public:

    IteratorTree(const IteratorTree< Key, Value, Compare >&) = default;
    IteratorTree< Key, Value, Compare >& operator=(const IteratorTree< Key, Value, Compare >&) = default;
    IteratorTree(IteratorTree< Key, Value, Compare >&& other) noexcept = default;
    IteratorTree< Key, Value, Compare >& operator=(IteratorTree< Key, Value, Compare >&& other) noexcept = default;


    IteratorTree():
      node_(nullptr)
    {}

    std::pair< Key, Value >& operator*()
    {
      return node_->data;
    }

    std::pair< Key, Value >* operator->()
    {
      return std::addressof(node_->data);
    }

    const std::pair< Key, Value >& operator*() const
    {
      return node_->data;
    }

    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(node_->data);
    }

    IteratorTree< Key, Value, Compare >& operator++()
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

    IteratorTree< Key, Value, Compare >& operator++(int)
    {
      IteratorTree< Key, Value, Compare > result(*this);
      ++(*this);
      return result;
    }

    bool operator==(const IteratorTree< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator==(ConstIteratorTree< Key, Value, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const IteratorTree< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }

    bool operator!=(ConstIteratorTree< Key, Value, Compare >& rhs) const
    {
      return !(*this == rhs);
    }

    ~IteratorTree() = default;
    private:
      detail::TreeNode< Key, Value >* node_;

      IteratorTree(detail::TreeNode< Key, Value >* node):
        node_(node)
      {}
  };
}

#endif
