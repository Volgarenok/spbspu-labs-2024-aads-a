#ifndef NODE_HPP
#define NODE_HPP

namespace marishin
{
  template < typename T >
  struct Node
  {
    Node(const T & value):
      data_(value),
      prev_(nullptr),
      next_(nullptr)
    {}
    T data_;
    Node * next_;
    Node * prev_;
  };
}

#endif
