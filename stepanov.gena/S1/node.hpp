#ifndef NODE_HPP
#define NODE_HPP

namespace stepanov
{
  template < typename T >
  struct Node
  {
    T data_;
    Node< T > * next_;

    Node(const T & data):
      data_(data),
      next_(nullptr)
    {}
  };
}

#endif
