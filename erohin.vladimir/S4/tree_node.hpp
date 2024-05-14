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
      std::pair< Key, T > data_;
      Node * parent_;
      Node * left_;
      Node * right_;
      unsigned short int color_;
      Node(const std::pair< Key, T > & value, Node * parent, Node * left, Node * right);
      Node(std::pair< Key, T > && value, Node * parent, Node * left, Node * right);
      ~Node() = default;
      Node * next();
      Node * prev();
    };

    template< class Key, class T >
    Node< Key, T >::Node(const std::pair< Key, T > & value, Node * parent, Node * left, Node * right):
      data_(value),
      parent_(parent),
      left_(left),
      right_(right),
      color_(color_t::RED)
    {}

    template< class Key, class T >
    Node< Key, T >::Node(std::pair< Key, T > && value, Node * parent, Node * left, Node * right):
      data_(std::move(value)),
      parent_(parent),
      left_(left),
      right_(right),
      color_(color_t::RED)
    {}

    template< class Key, class T >
    Node< Key, T > * Node< Key, T >::next()
    {
      Node< Key, T > * node = this;
      if (node->right_)
      {
        node = node->right_;
        while (node->left_)
        {
          node = node->left_;
        }
      }
      else
      {
        if (!parent_)
        {
          return nullptr;
        }
        while (node->parent_->right_ == node)
        {
          node = node->parent_;
          if (!node->parent_)
          {
            return nullptr;
          }
        }
        while (node->parent_ && node->parent_->left_ == node)
        {
          node = node->parent_;
        }
      }
      return node;
    }

    template< class Key, class T >
    Node< Key, T > * Node< Key, T >::prev()
    {
      Node< Key, T > * node = this;
      if (node->left_)
      {
        node = node->left_;
        while (node->right_)
        {
          node = node->right_;
        }
      }
      else
      {
        while (node->parent_->left_ == node)
        {
          node = node->parent_;
          if (!(node->parent_))
          {
            return nullptr;
          }
        }
        while (node->parent_ && node->parent_->right_ == node)
        {
          node = node->parent_;
        }
      }
      return node;
    }
  }
}

#endif
