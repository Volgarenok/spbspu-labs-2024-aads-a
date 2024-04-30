#ifndef TRAVERSAL_STRATEGY_HPP
#define TRAVERSAL_STRATEGY_HPP

#include "tree_node.hpp"

namespace erohin
{
  namespace detail
  {
    template< class Key, class T >
    struct InfixTraversal
    {
      Node< Key, T > * next(Node< Key, T > * node);
      Node< Key, T > * prev(Node< Key, T > * node);
    };

    template< class Key, class T >
    struct PostfixTraversal
    {
      Node< Key, T > * next(Node< Key, T > * node);
      Node< Key, T > * prev(Node< Key, T > * node);
    };

    template< class Key, class T >
    Node< Key, T > * InfixTraversal< Key, T >::next(Node< Key, T > * node)
    {
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
        while (node->parent_->right_ == node)
        {
          node = node->parent_;
        }
        while (node->parent_ && node->parent_->left_ == node && !(node->right_))
        {
          node = node->parent_;
        }
      }
      return node;
    }

    template< class Key, class T >
    Node< Key, T > * InfixTraversal< Key, T >::prev(Node< Key, T > * node)
    {
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
        while (node->parent_ && node->parent_->left_ == node)
        {
          node = node->parent_;
        }
        node = node->parent_;
      }
      return node;
    }

    template< class Key, class T >
    Node< Key, T > * PostfixTraversal< Key, T >::next(Node< Key, T > * node)
    {
      if (node->parent_ && node->parent_->left_ == node)
      {
        node = node->parent_;
        if (node = node->right_)
        {
          node = node->right_;
          while (node->left_)
          {
            node = node->left_;
          }
        }
      }
      else if (node->parent_ && node->parent_->right_ == node)
      {
        node = node->parent_;
      }
      return node;
    }

    template< class Key, class T >
    Node< Key, T > * PostfixTraversal< Key, T >::prev(Node< Key, T > * node)
    {
      if (node->parent_ && node->parent_->right_ == node)
      {
        node = node->parent_;
        if (node = node->left_)
        {
          node = node->left_;
          while (node->right_)
          {
            node = node->right_;
          }
        }
      }
      else if (node->parent_ && node->parent_->left_ == node)
      {
        node = node->parent_;
      }
      return node;
    }
  }
}

#endif
