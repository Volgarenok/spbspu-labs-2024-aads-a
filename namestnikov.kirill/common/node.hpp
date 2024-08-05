#ifndef NODE_HPP
#define NODE_HPP

namespace namestnikov
{
  namespace detail
  {
    template< class T >
    struct Node
    {
      explicit Node(const T & data):
        data_(data),
        next_(nullptr)
      {}
      ~Node() = default;
      T data_;
      Node * next_;
    };
  }
}

#endif
