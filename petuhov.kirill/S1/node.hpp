#ifndef NODE_HPP
#define NODE_HPP

namespace petuhov
{
  namespace detail
  {
    template < typename T >
    struct Node
    {
      T value_;
      Node *next_;

      Node();
      Node(const T& value):
        value_(value),
        next_(nullptr)
      {}
      Node(const T& value, Node *next):
        value_(value),
        next_(next)
      {}
      ~Node() = default;
    };
  }
}

#endif
