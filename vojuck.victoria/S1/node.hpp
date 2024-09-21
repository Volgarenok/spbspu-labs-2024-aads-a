#ifndef NODE_HPP
#define NODE_HPP

namespace vojuck
{
  template< typename T >
  struct Node
  {
    T _data;
    Node * next_;

  Node(const T & data):
    data_(value),
    next_(nullptr)
    {}
  };
}

#endif
