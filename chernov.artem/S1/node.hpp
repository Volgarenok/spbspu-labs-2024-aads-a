#ifndef NODE_HPP
#define NODE_HPP

template < typename T >
struct Node
{
  Node() = default;
  Node(Node< T >* next, T value) : next_(next), data_(value)
  {}
  T data_;
  Node< T >* next_;
};

#endif
