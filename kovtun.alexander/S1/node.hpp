#ifndef NODE_HPP
#define NODE_HPP

#include <stddef.h>

namespace kovtun
{
  template<typename T>
  struct Node
  {
    Node(Node * prev, Node * next, T val);
    Node(const T & val);
    ~Node() = default;

    Node * prev;
    Node * next;
    T val;
  };

  template< typename T >
  Node< T >::Node(Node<T> *prev, Node<T> *next, T val) :
      prev(prev),
      next(next),
      val(val)
  {}

  template< typename T >
  Node< T >::Node(const T & val) :
      Node(nullptr, nullptr, val)
  {}
}

#endif
