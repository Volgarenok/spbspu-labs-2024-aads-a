#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>

namespace erohin
{
  namespace detail
  {
    template< class T >
    struct TreeNode
    {
      T data_;
      TreeNode * parent_;
      TreeNode * left_;
      TreeNode * right_;
      TreeNode(const T & value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node);
      TreeNode(T && value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node);
      ~TreeNode() = default;
    };

    template< class T >
    TreeNode< T >::TreeNode(const T & value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node):
      data_(value),
      parent_(parent_node),
      left_(left_node),
      right_(right_node)
    {}

    template< class T >
    TreeNode< T >::TreeNode(T && value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node):
      data_(std::move(value)),
      parent_(parent_node),
      left_(left_node),
      right_(right_node)
    {}
  }
}

#endif
