#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace namestnikov
{
  namespace detail
  {
    template< class Key, class Value >
    struct TreeNode
    {
      using node_t = detail::TreeNode< Key, Value >;
      std::pair< Key, Value > data;
      node_t * parent;
      node_t * left;
      node_t * right;
      int height;
      TreeNode(Key key, Value val, TreeNode * parent = nullptr, TreeNode * left = nullptr, TreeNode * right = nullptr, int height = 0)
      {
        data.first = key;
        data.second = val;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->height = height;
      }

      int getHeight(node_t * root)
      {
        if (!root)
        {
          return -1;
        }
        else
        {
          int leftHeight = getHeight(root->left);
          int rightHeight = getHeight(root->right);
          return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
        }
      }
      bool isLeftChild() const
      {
        return (this->parent) && (this->parent->left == this);
      }
      bool isRightChild() const
      {
        return (this->parent) && (this->parent->right == this);
      }
      bool isRoot() const
      {
        return !this->parent;
      }
    };
  }
}

#endif