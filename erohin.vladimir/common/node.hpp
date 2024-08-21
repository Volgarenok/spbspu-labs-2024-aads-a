#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace erohin
{
  namespace detail
  {
    template< class T >
    struct Node
    {
      T data_;
      Node * next_;
      Node(const T & value, Node * next_node);
      Node(T && value, Node * next_node);
      ~Node() = default;
    };

    template< class T >
    Node< T >::Node(const T & value, Node * next_node):
      data_(value),
      next_(next_node)
    {}

    template< class T >
    Node< T >::Node(T && value, Node * next_node):
      data_(std::move(value)),
      next_(next_node)
    {}
  }
}

#endif
