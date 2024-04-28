#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>

namespace erohin
{
  namespace detail
  {
    template< class Key, class T >
    struct TreeNode
    {
      std::pair< Key, T > data_;
      TreeNode * parent_;
      TreeNode * left_;
      TreeNode * right_;
      TreeNode(const Key & key, const T & value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node);
      TreeNode(const Key & key, T && value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node);
      ~TreeNode() = default;
    };

    template< class Key, class T >
    TreeNode< Key, T >::TreeNode(const Key & key, const T & value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node):
      data_(std::make_pair(key, value)),
      parent_(parent_node),
      left_(left_node),
      right_(right_node)
    {}

    template< class Key, class T >
    TreeNode< Key, T >::TreeNode(const Key & key, T && value, TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node):
      data_(std::make_pair(key, std::move(value))),
      parent_(parent_node),
      left_(left_node),
      right_(right_node)
    {}
  }
}

#endif
