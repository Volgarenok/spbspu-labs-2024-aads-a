#ifndef NODE_HPP
#define NODE_HPP

namespace vojuck
{
  namespace details
  {
    template< typename T >
    struct Node
    {
      T data_;
      Node< T > * next_;

      Node():
        data_(),
        next_(nullptr)
      {}
      Node(const T & data):
        data_(data),
        next_(nullptr)
      {}
      Node(const Node< T > * other):
        data_(other->data_),
        next_(other->next_)
      {}
    };
  }
}

#endif
