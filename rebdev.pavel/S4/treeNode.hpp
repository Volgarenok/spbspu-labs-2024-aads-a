#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace rebdev
{
  template < class T >
  struct TreeNode
  {
    TreeNode * parent;
    TreeNode * right;
    TreeNode * left;
    T data;
  };
}

#endif
