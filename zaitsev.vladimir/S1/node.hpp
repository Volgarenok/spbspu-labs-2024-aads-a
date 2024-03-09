#ifndef NODE_HPP
#define NODE_HPP
#include <stdexcept>
#include <cstddef>

namespace zaitsev
{
  template< typename T >
  struct Node
  {
    T value_;
    Node* next_;
    Node() = default;
    Node(const T& value);
    Node(T&& value);
    ~Node() = default;
  };

  template< typename T >
  Node< T >::Node(const T& value):
    value_(value),
    next_(nullptr)
  {}

  template< typename T >
  Node< T >::Node(T&& value):
    value_(value),
    next_(nullptr)
  {}

  template< typename T >
  void freeNodes(Node< T >* head_node)
  {
    while (head_node)
    {
      Node< T >* temp = head_node->next_;
      delete head_node;
      head_node = temp;
    }
  }
}
#endif
