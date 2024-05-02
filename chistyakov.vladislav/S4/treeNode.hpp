#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace chistyakov
{
  template< typename T >
  struct TreeNode
  {
    TreeNode()
    {
      value = 0,
      parent = nullptr,
      left = nullptr,
      right = nullptr,
    }

    TreeNode(TreeNode * left, TreeNode * right, TreeNode * parent, T value)
      left(left),
      right(right),
      parent(parent),
      value(value)
    {}

    bool isRoot()
    {
      return (parent == nullptr);
    }

    bool isLeftCh()
    {
      return (parent->left == this);
    }

    bool isRightCh()
    {
      return (parent->right == this);
    }

    T value;
    TreeNode< T > * parent;
    TreeNode< T > * left;
    TreeNode< T > * right;
  };
}

#endif

