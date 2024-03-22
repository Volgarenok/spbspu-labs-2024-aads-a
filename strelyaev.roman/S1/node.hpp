#ifndef NODE_HPP
#define NODE_HPP
namespace strelyaev
{
  template< typename T >
  struct Node
  {
    Node(T value):
      value_(value),
      next_(nullptr),
      prev_(nullptr)
    {}
    ~Node() = default;
    T value_;
    Node* next_;
    Node* prev_;
  };
}
#endif
