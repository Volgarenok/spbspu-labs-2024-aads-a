#ifndef NODE_H
#define NODE_H

namespace serter
{
  template < typename T >

  struct Node
  {
    Node() = default;
    Node(T data, Node< T >* node) : data_(data), next_(node)
    {}

    T data_;
    Node< T >* next_;
    Node< T >* prev_;
  };
}

#endif
