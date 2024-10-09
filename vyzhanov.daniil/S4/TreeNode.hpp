#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace vyzhanov
{
  template< class Key, class Value >
  struct Node
  {
    std::pair< Key, Value > data;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;
    Node(const Key& key, const Value& value);
    Node(const Key& key, const Value& val, Node* parent);
    bool isLeftChild() const;
    bool isRightChild() const;
    bool isRoot() const;
   };
  template< class Key, class Value >
  Node< Key, Value >::Node(const Key& key, const Value& value)
  {
    data = std::make_pair(key, value);
    height = 0;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
  }

  template< class Key, class Value >
  Node< Key, Value >::Node(const Key& key, const Value& val, Node* parent)
  {
    data = std::make_pair(key, value);
    parent = newParent;
    left = nullptr;
    right = nullptr;
    height = 0;
  }

  template< class Key, class Value >
  bool Node< Key, Value >::isLeftChild() const
  {
    return (this->parent) && (this->parent->left == this)
  }

  template< class Key, class Value >
  bool Node< Key, Value >::isRightChild() const
  {
    return (this->parent) && (this->parent->right == this)
  }

  template< class Key, class Value >
  bool Node< Key, Value >::isRoot() const
  {
    return !(this->parent)
  }
}

#endif
