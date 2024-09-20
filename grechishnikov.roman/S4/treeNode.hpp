#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace grechishnikov
{
  namespace detail
  {
    template< typename Key, typename T >
    struct Node
    {
      std::pair< Key, T > data_;
      Node* parent_;
      Node* left_;
      Node* right_;
      Node(Key key, const T& data, Node* parent, Node* left, Node* right);
    };

    template< typename Key, typename T >
    Node< Key, T >::Node(Key key, const T& data, Node* parent, Node* left, Node* right):
      data_(key, data),
      parent_(parent),
      left_(left),
      right_(right)
    {}

    template< typename Key, typename T >
    Node< Key, T >* goAllLeft(Node< Key, T >* node)
    {
      if (!node)
      {
        return node;
      }
      while (node->left_)
      {
        node = node->left_;
      }
      return node;
    }

    template< typename Key, typename T >
    Node< Key, T >* goAllRight(Node< Key, T >* node)
    {
      if (!node)
      {
        return node;
      }
      while (node->right_)
      {
        node = node->right_;
      }
      return node;
    }

    template< typename Key, typename T >
    bool isRightNode(Node< Key, T >* node)
    {
      if (!node->parent_)
      {
        return false;
      }
      return node == node->parent_->right_;
    }

    template< typename Key, typename T >
    bool isLeftNode(Node< Key, T >* node)
    {
      if (!node->parent_)
      {
        return false;
      }
      return node == node->parent_->left_;
    }
  }
}

#endif

