#ifndef NODE_HPP
#define NODE_HPP

namespace vojuck
{
  namespace detail
  {
    template< typename T >
    struct Node
    {
      T data_;
      Node * next_;

    Node(const T & data):
      data_(value),
      next_(nullptr)
      {}
    };
  }
}

#endif
