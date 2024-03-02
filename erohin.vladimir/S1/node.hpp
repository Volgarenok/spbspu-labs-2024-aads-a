#ifndef NODE_HPP
#define NODE_HPP

namespace erohin
{
  template< class T >
  class Node
  {
  public:
    T data_;
    Node * next_;
    Node(const T & value, Node * const next_node);
    Node(T && value, Node * const next_node);
    ~Node() = default;
  };

  template< class T >
  Node< T >::Node(const T & value, Node * const next_node):
    data_(value),
    next_(next_node)
  {}

  template< class T >
  Node< T >::Node(T && value, Node * const next_node):
    data_(value),
    next_(next_node)
  {}
}

#endif
