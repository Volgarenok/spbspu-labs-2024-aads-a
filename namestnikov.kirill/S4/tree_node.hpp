#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace namestnikov
{
  template< class T >
  struct TreeNode
  {
    using node_t = TreeNode< T >;
    T data;
    node_t * parent;
    node_t * left;
    node_t * right;
    int height;
    TreeNode(const T & value):
      data(value),
      parent(nullptr),
      left(nullptr),
      right(nullptr)
    {}
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
  };
}

#endif