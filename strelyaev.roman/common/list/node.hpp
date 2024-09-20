#ifndef NODE_HPP
#define NODE_HPP
namespace strelyaev
{
  namespace detail
  {
    template< typename T >
    struct Node
    {
      Node(Node* prev, Node* next):
        value_(T()),
        next_(next),
        prev_(prev)
      {}
      Node(const T& value):
        value_(value),
        next_(nullptr),
        prev_(nullptr)
      {}
      Node(Node* prev, Node* next, const T& value):
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
}
#endif
