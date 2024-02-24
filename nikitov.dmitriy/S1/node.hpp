#ifndef NODE_HPP
#define NODE_HPP

namespace nikitov
{
  template< typename T >
  struct Node
  {
  public:
    Node():
      value_(0),
      next_(nullptr),
      prev_(nullptr)
    {}
    Node(T value, Node* next, Node* prev):
      value_(value),
      next_(next),
      prev_(prev)
    {}
    ~Node() = default;
    T value_;
    Node* next_;
    Node* prev_;
  };
}
#endif
