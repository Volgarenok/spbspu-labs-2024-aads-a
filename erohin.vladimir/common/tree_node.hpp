#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <cstddef>

namespace erohin
{
  namespace detail
  {
    enum color_t
    {
      BLACK,
      RED
    };

    template< class Key, class T >
    struct TreeNode
    {
      std::pair< Key, T > data;
      TreeNode * parent;
      TreeNode * left;
      TreeNode * right;
      color_t color;
      template< class... Args >
      TreeNode(TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node, Args &&... args);
      ~TreeNode() = default;
      TreeNode * next();
      TreeNode * prev();
    };

    template< class Key, class T >
    template< class... Args >
    TreeNode< Key, T >::TreeNode(TreeNode * parent_node, TreeNode * left_node, TreeNode * right_node, Args &&... args):
      data(std::forward< Args... >(args...)),
      parent(parent_node),
      left(left_node),
      right(right_node),
      color(color_t::RED)
    {}

    template< class Key, class T >
    TreeNode< Key, T > * TreeNode< Key, T >::next()
    {
      TreeNode< Key, T > * node = this;
      if (node->right)
      {
        node = node->right;
        while (node->left)
        {
          node = node->left;
        }
      }
      else
      {
        while (node->parent && node->parent->left != node)
        {
          node = node->parent;
        }
        if (!node->parent)
        {
          return nullptr;
        }
        node = node->parent;
      }
      return node;
    }

    template< class Key, class T >
    TreeNode< Key, T > * TreeNode< Key, T >::prev()
    {
      TreeNode< Key, T > * node = this;
      if (node->left)
      {
        node = node->left;
        while (node->right)
        {
          node = node->right;
        }
      }
      else
      {
        while (node->parent && node->parent->right != node)
        {
          node = node->parent;
        }
        if (!node->parent)
        {
          return nullptr;
        }
        node = node->parent;
      }
      return node;
    }
  }
}

#endif
