#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP
#include <memory>
#include "treeNode.hpp"

namespace strelyaev
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T >
  struct ConstIteratorTree
  {
    friend class Tree< Key, T, std::less< Key > >;
    public:
      ConstIteratorTree(const ConstIteratorTree< Key, T >& val):
        node_(val.node_)
      {}

      ConstIteratorTree< Key, T >& operator=(const ConstIteratorTree< Key, T>& rhs) = default;

      const std::pair< Key, T >& operator*() const
      {
        return node_->data_;
      }

      const std::pair< Key, T >* operator->() const
      {
        return std::addressof(node_->data_);
      }

      ConstIteratorTree< Key, T >& operator++()
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

      ConstIteratorTree< Key, T > operator++(int)
      {
        ConstIteratorTree< Key, T > result(*this);
        ++(*this);
        return result;
      }

      ConstIteratorTree< Key, T > operator--()
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

      ConstIteratorTree< Key, T > operator--(int)
      {
        ConstIteratorTree< Key, T > result(*this);
        --(*this);
        return result;
      }

      bool operator==(ConstIteratorTree< Key, T > rhs)
      {
        return node_ == rhs.node_;
      }

      bool operator!=(ConstIteratorTree< Key, T > rhs)
      {
        return !(*this == rhs);
      }

    private:
      detail::TreeNode< Key, T >* node_;

      explicit ConstIteratorTree(detail::TreeNode< Key, T >* node):
        node_(node)
      {}
  };

}

#endif
