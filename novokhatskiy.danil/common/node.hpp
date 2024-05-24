#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace novokhatskiy
{
  namespace detail
  {
    template < typename T >
    struct Node
    {
      T value_;
      Node* next_;
      Node(const T& value = 0, Node* next = nullptr):
        value_(value),
        next_(next)
      {}
      Node(T&& value):
        value_(std::move(value)),
        next_(nullptr)
      {}
      template < class... Args >
      explicit Node(Node* next, Args&&... args):
        value_(std::forward< Args >(args)...),
        next_(next)
      {}
    };
    template < typename T >
    void freeNode(Node< T >* other) noexcept
    {
      while (other)
      {
        Node< T >* tmp = other->next_;
        delete other;
        other = tmp;
      }
    }
  }
}
#endif
