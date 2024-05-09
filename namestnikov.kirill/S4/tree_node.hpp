#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace namestnikov
{
  namespace detail
  {
    template< class T >
    struct TreeNode
    {
      using node_t = detail::TreeNode< T >;
      T data;
      node_t * parent;
      node_t * left;
      node_t * right;
      int height;
      explicit TreeNode(const T & value):
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