#ifndef NODE_HPP
#define NODE_HPP

template < typename T >
struct Node
{
  Node() = default;
  T data_;
  Node< T >* next_;
};

#endif
