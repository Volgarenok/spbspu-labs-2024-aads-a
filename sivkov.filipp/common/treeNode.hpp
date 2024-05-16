#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace sivkov
{
  namespace detail
  {
    template < typename Key, typename Value >
    struct TreeNode
    {
      TreeNode* left;
      TreeNode* right;
      TreeNode* parent;
      std::pair< Key, Value > data;

      TreeNode():
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(std::pair< Key, Value >())
      {}

      TreeNode(const Key& key, const Value& value):
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(std::make_pair(key, value))
      {}

      TreeNode< Key, Value >* rotate_right(TreeNode< Key, Value >* root)
      {
        TreeNode< Key, Value >* new_root = root->left;
        root->left = new_root->right;
        if (new_root->right != nullptr)
        {
          new_root->right->parent = root;
        }
        new_root->right = root;
        new_root->parent = root->parent;
        root->parent = new_root;
        return new_root;
      }

      TreeNode< Key, Value >* rotate_left(TreeNode< Key, Value >* root)
      {
        TreeNode< Key, Value >* new_root = root->right;
        root->right = new_root->left;
        if (new_root->left != nullptr)
        {
          new_root->left->parent = root;
        }
        new_root->left = root;
        new_root->parent = root->parent;
        root->parent = new_root;
        return new_root;
      }
    };
  }
}

#endif
