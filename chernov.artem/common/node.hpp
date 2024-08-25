#ifndef NODE_HPP
#define NODE_HPP

namespace chernov
{
  template < typename T >
  struct Node
  {
    Node(const T& value):
      data_(value),
      next_(nullptr)
    {}
    T data_;
    Node< T >* next_;
    ~Node() = default;
  };
}

#endif
