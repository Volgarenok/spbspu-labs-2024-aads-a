#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace erohin
{
  namespace detail
  {
    template< class T >
    class Node
    {
    public:
      T data_;
      Node * next_;
      Node(const T & value, const Node * next_node);
      Node(T && value, const Node * next_node);
      ~Node() = default;
    };

    template< class T >
    Node< T >::Node(const T & value, const Node * next_node):
      data_(value),
      next_(const_cast< Node * >(next_node))
    {}

    template< class T >
    Node< T >::Node(T && value, const Node * next_node):
      data_(std::move(value)),
      next_(const_cast< Node * >(next_node))
    {}
  }
}

#endif
