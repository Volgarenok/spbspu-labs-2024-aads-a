#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace zhalilov
{
  namespace detail
  {
    enum class NodeType
    {
      Two,
      Three
    };

    template < class T >
    struct TreeNode
    {
      TreeNode *parent;
      TreeNode *left;
      TreeNode *mid;
      TreeNode *right;
      T one;
      T two;
      NodeType type;
    };

  }
}

#endif
