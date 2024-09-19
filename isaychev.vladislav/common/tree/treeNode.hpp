#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace isaychev
{
  namespace detail
  {
    template < class Key, class Value >
    struct TreeNode
    {
      std::pair< Key, Value > data;
      TreeNode< Key, Value > * right;
      TreeNode< Key, Value > * left;
      TreeNode< Key, Value > * parent;

      TreeNode (Key key, Value value, TreeNode< Key, Value > * root):
       data(key, value),
       right(nullptr),
       left(nullptr),
       parent(root)
      {}
    };

    template < class Key, class Value >
    TreeNode< Key, Value > * traverse_left(TreeNode< Key, Value > * root)
    {
      if (root)
      {
        while (root->left)
        {
          root = root->left;
        }
      }
      return root;
    }

    template < class Key, class Value >
    TreeNode< Key, Value > * traverse_right(TreeNode< Key, Value > * root)
    {
      if (!root)
      {
        return root;
      }
      return root->right ? traverse_right(root->right) : root;
    }

    template < class Key, class Value >
    TreeNode< Key, Value > * go_up(TreeNode< Key, Value > * current)
    {
      return current->parent;
    }
  }
}

#endif
