#ifndef NODE_HPP
#define NODE_HPP

namespace baranov
{
  template< class T >
  struct Node
  {
    Node(const T & data):
      data_(data),
      next_(nullptr),
      prev_(nullptr)
    {}
    T data_;
    Node * next_;
    Node * prev_;
  };
}

#endif
