#ifndef TREENODE_HPP
#define TREENODE_HPP


#include <utility>

namespace marishin
{
  namespace detail
  {
    template< typename Key, typename Value >
    struct TreeNode
    {
      std::pair< Key, Value > data;
      detail::TreeNode< Key, Value >* left;
      detail::TreeNode< Key, Value >* right;
      detail::TreeNode< Key, Value >* parent;
      int height;

      TreeNode(const Key& key, const Value& val)
      {
        data = std::make_pair(key, val);
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 0;
      }

      TreeNode(const Key& key, const Value& val, TreeNode* newParent)
      {
        data = std::make_pair(key, val);
        left = nullptr;
        right = nullptr;
        parent = newParent;
        height = 0;
      }

      bool isLeft() const noexcept
      {
        return this->parent && this->parent->left == this;
      }

      bool isRight() const noexcept
      {
        return this->parent && this->parent->right == this;
      }

      bool isRoot() const noexcept
      {
        return !this->parent;
      }

    };
  }
}

#endif
