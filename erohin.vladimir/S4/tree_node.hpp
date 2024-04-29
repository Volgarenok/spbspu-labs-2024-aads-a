#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <cstddef>

namespace erohin
{
  namespace detail
  {
    template< class Key, class T >
    struct Node
    {
      std::pair< Key, T > data_;
      Node * parent_;
      Node * left_;
      Node * right_;
      unsigned short int color_;
      size_t height_;
      Node(const std::pair< Key, T > & value, Node * parent, Node * left, Node * right);
      Node(std::pair< Key, T > && value, Node * parent, Node * left, Node * right);
      ~Node() = default;
    };

    template< class Key, class T >
    Node< Key, T >::Node(const std::pair< Key, T > & value, Node * parent, Node * left, Node * right):
      data_(value),
      parent_(parent),
      left_(left),
      right_(right),
      color_(1),
      height_(0)
    {}

    template< class Key, class T >
    Node< Key, T >::Node(std::pair< Key, T > && value, Node * parent, Node * left, Node * right):
      data_(std::move(value)),
      parent_(parent),
      left_(left),
      right_(right),
      color_(1),
      height_(0)
    {}
  }
}

#endif
