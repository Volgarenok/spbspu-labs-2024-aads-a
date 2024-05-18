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
    struct Node
    {
      std::pair< Key, T > data;
      Node * parent;
      Node * left;
      Node * right;
      color_t color;
      template< class... Args >
      Node(Node * parent_node, Node * left_node, Node * right_node, Args &&... args);
      ~Node() = default;
      Node * next();
      Node * prev();
    };

    template< class Key, class T >
    template< class... Args >
    Node< Key, T >::Node(Node * parent_node, Node * left_node, Node * right_node, Args &&... args):
      data(std::forward< Args... >(args...)),
      parent(parent_node),
      left(left_node),
      right(right_node),
      color(color_t::RED)
    {}

    template< class Key, class T >
    Node< Key, T > * Node< Key, T >::next()
    {
      Node< Key, T > * node = this;
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
        if (!parent)
        {
          return nullptr;
        }
        while (node->parent->right == node)
        {
          node = node->parent;
          if (!node->parent)
          {
            return nullptr;
          }
        }
        while (node->parent && node->parent->left == node)
        {
          node = node->parent;
        }
      }
      return node;
    }

    template< class Key, class T >
    Node< Key, T > * Node< Key, T >::prev()
    {
      Node< Key, T > * node = this;
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
        while (node->parent->left == node)
        {
          node = node->parent;
          if (!(node->parent))
          {
            return nullptr;
          }
        }
        while (node->parent && node->parent->right == node)
        {
          node = node->parent;
        }
      }
      return node;
    }
  }
}

#endif
