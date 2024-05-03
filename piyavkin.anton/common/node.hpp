#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace piyavkin
{
  namespace detail
  {
    template< class T >
    struct Node
    {
      template< class... Args >
      Node(Node* next, Node* prev, Args&& ...args):
        value_(std::forward< Args >(args)...),
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
