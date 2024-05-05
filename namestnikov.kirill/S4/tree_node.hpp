#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

namespace namestnikov
{
  template< class T >
  struct TreeNode
  {
    T data;
    TreeNode< T > * parent;
    TreeNode< T > * left;
    TreeNode< T > * right;
    size_t height;
  };
}

#endif