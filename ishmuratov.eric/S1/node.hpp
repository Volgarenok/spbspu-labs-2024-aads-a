#ifndef NODE_HPP
#define NODE_HPP

namespace ishmuratov
{
  template< class T >
  struct Node
  {
    Node(T data):
      data_(data),
      next_(nullptr),
      prev_(nullptr)
    {}
    T data_;
    Node * prev_;
    Node * next_;
  };
}

#endif
