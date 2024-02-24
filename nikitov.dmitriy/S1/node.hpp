#ifndef NODE_HPP
#define NODE_HPP

namespace nikitov
{
  template< typename T >
  struct Node
  {
  public:
    Node(T value):
      value_(value),
      prev_(nullptr),
      next_(nullptr)
    {}
    ~Node() = default;
    T value_;
    Node* prev_;
    Node* next_;
  };
}
#endif
