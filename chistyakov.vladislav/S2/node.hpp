#ifndef NODE_HPP
#define NODE_HPP

namespace chistyakov
{
  template< typename T >
  struct Node
  {
    Node(const T & value):
      value_(value),
      next_(nullptr),
      previous_(nullptr)
    {}

    ~Node() = default;

    T value_;
    Node * next_;
    Node * previous_;
  };
}

#endif
