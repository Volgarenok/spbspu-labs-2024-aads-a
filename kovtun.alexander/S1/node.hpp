#ifndef NODE_HPP
#define NODE_HPP

#include <stddef.h>

namespace kovtun
{
  template<typename T>
  struct Node
  {
    Node() = default;
    ~Node() = default;
    Node(Node * prev, Node * next, const T & val);
    explicit Node(const T & val);

    Node * prev;
    Node * next;
    T val;
  };

  template< typename T >
  Node< T >::Node(Node<T> *prev, Node<T> *next, const T & val) :
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
