#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <utility>
#include <algorithm>

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
      color_t * color_;
      size_t height_;
      Node(const Key & key, const T & value, Node * parent, Node * left, Node * right, color_t clr);
      Node(const Key & key, T && value, Node * parent, Node * left, Node * right, color_t clr);
      Node(Key && key, const T & value, Node * parent, Node * left, Node * right, color_t clr);
      Node(Key && key, T && value, Node * parent, Node * left, Node * right, color_t clr);
      ~Node() = default;
    };

    template< class Key, class T >
    Node< Key, T >::Node(const Key & key, const T & value, Node * parent, Node * left, Node * right, color_t clr):
      data_(std::make_pair(key, value)),
      parent_(parent),
      left_(left),
      right_(right),
      color_(clr),
      height_(0)
    {}

    template< class Key, class T >
    Node< Key, T >::Node(const Key & key, T && value, Node * parent, Node * left, Node * right, color_t clr):
      data_(std::make_pair(key, std::move(value))),
      parent_(parent),
      left_(left),
      right_(right),
      color_(clr),
      height_(0)
    {}

    template< class Key, class T >
    Node< Key, T >::Node(Key && key, const T & value, Node * parent, Node * left, Node * right, color_t clr):
      data_(std::make_pair(std::move(key), value)),
      parent_(parent),
      left_(left),
      right_(right),
      color_(clr),
      height_(0)
    {}

    template< class Key, class T >
    Node< Key, T >::Node(Key && key, T && value, Node * parent, Node * left, Node * right, color_t clr):
      data_(std::make_pair(std::move(key), std::move(value))),
      parent_(parent),
      left_(left),
      right_(right),
      color_(clr),
      height_(0)
    {}
  }
}

#endif
