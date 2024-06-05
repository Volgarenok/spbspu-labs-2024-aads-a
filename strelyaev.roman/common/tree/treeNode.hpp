#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>
#include <cstddef>
namespace strelyaev
{
  namespace detail
  {
    template< typename Key, typename T >
    struct TreeNode
    {
      TreeNode(TreeNode* left, TreeNode* parent, TreeNode* right, Key key, T value):
        data_(std::make_pair(key, value)),
        parent_(parent),
        right_(right),
        left_(left),
        height_(0)
      {}

      bool isRoot() noexcept
      {
        return (parent_ == nullptr);
      }

      bool isLeftChild() noexcept
      {
        return (parent_->left_ == this);
      }

      bool isRightChild() noexcept
      {
        return (parent_->right_ == this);
      }

      std::pair< Key, T > data_;
      TreeNode< Key, T >* parent_;
      TreeNode< Key, T >* right_;
      TreeNode< Key, T >* left_;
      size_t height_;
    };
  }
}
#endif
