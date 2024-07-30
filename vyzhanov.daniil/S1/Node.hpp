#ifndef NODE_HPP
#define NODE_HPP
namespace vyzhanov
{
  template< typename T >
  struct Node
  {
    T data_;
    Node* next_;
    Node* prev_;

    Node(const T& data, Node* next, Node* prev);
    ~Node() = default;
  };

  template< typename T >
  Node< T >::Node(const T& data, Node* next, Node* prev):
    data_(data),
    next_(next),
    prev_(prev)
  {}
}
#endif
