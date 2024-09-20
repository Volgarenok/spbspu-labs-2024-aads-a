#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP
#include <utility>

namespace baranov
{
  template< typename Key, typename T >
  struct TreeNode
  {
    TreeNode(Key key, T val, TreeNode * left, TreeNode * right, TreeNode * parent):
      data_(std::make_pair(key, val)),
      left_(left),
      right_(right),
      parent_(parent)
    {}
    std::pair< Key, T > data_;
    TreeNode< Key, T > * left_;
    TreeNode< Key, T > * right_;
    TreeNode< Key, T  > * parent_;

    bool hasLeft() const noexcept
    {
      return left_ != nullptr;
    }

    bool hasRight() const noexcept
    {
      return right_ != nullptr;
    }

    bool isRoot() const noexcept
    {
      return parent_ == nullptr;
    }

    bool isLeft() const noexcept
    {
      return !isRoot() && parent_->left_ == this;
    }

    bool isRight() const noexcept
    {
      return !isRoot() && parent_->right_ == this;
    }
  };
}

#endif

