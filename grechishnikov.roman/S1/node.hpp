#ifndef NODE_HPP
#define NODE_HPP

namespace grechishnikov
{
  template< typename T >
  struct Node
  {
    T data_;
    Node* prev_;
    Node* next_;
    Node();
    Node(const T& data, Node* prev, Node* next);
  };

  template< typename T >
  Node< T >::Node():
    data_(T()),
    prev_(nullptr),
    next_(nullptr)
  {}

  template< typename T >
  Node< T >::Node(const T& data, Node* prev, Node* next):
    data_(data),
    prev_(prev),
    next_(next)
  {}
}

#endif
