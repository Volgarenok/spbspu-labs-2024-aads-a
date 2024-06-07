#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include <memory>
#include "treeNode.hpp"

namespace strelyaev
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T >
  struct IteratorTree
  {
    friend class Tree< Key, T, std::less< Key > >;
    public:
      IteratorTree(const IteratorTree< Key, T >& val):
        node_(val.node_)
      {}

      IteratorTree< Key, T >& operator=(const IteratorTree< Key, T>& rhs) = default;

      std::pair< Key, T >& operator*()
      {
        return node_->data_;
      }

      std::pair< Key, T >* operator->()
      {
        return std::addressof(node_->data_);
      }

      IteratorTree< Key, T >& operator++()
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
        while (!node_->isRoot() && node_->isRightChild())
        {
          node_ = node_->parent_;
        }
        node_ = node_->parent_;
        return *this;
      }

      IteratorTree< Key, T > operator++(int)
      {
        IteratorTree< Key, T > result(*this);
        ++(*this);
        return result;
      }

      IteratorTree< Key, T > operator--()
      {
        if (node_->left_)
        {
          node_ = node_->left_;
          while (node_->right_)
          {
            node_ = node_->right_;
          }
          return *this;
        }
        while (node_->parent_ && node_->parent_->left_ == node_)
        {
          node_ = node_->parent_;
        }
        node_ = node_->parent_;
        return *this;
      }

      IteratorTree< Key, T > operator--(int)
      {
        IteratorTree< Key, T > result(*this);
        --(*this);
        return result;
      }

      bool operator==(const IteratorTree< Key, T >& rhs)
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const IteratorTree< Key, T >& rhs)
      {
        return !(*this == rhs);
      }

    private:
      detail::TreeNode< Key, T >* node_;

      explicit IteratorTree(detail::TreeNode< Key, T >* node):
        node_(node)
      {}
  };
}

#endif


