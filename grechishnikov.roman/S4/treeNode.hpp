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
  }

  template< typename Key, typename T >
  detail::Node< Key, T >::Node(Key key, const T& data, Node* parent, Node* left, Node* right):
    data_(key, data),
    parent_(parent),
    left_(left),
    right_(right)
  {}
}

#endif

