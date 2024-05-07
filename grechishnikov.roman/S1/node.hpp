#ifndef NODE_HPP
#define NODE_HPP

namespace grechishnikov
{
  namespace detail
  {
    template< typename T >
    struct Node
    {
      T data_;
      Node* prev_;
      Node* next_;
      Node(const T& data, Node* prev, Node* next);
    };
  }

  template< typename T >
  detail::Node< T >::Node(const T& data, Node* prev, Node* next):
    data_(data),
    prev_(prev),
    next_(next)
  {}
}

#endif
