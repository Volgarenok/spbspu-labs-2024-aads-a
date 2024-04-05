#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace zhalilov
{
  namespace detail
  {
    template < typename T >
    struct Node
    {
      T value;
      Node *prev;
      Node *next;

      Node(const T &avalue, Node *aprev, Node *anext):
        value(avalue),
        prev(aprev),
        next(anext)
      {}

      Node(T &&avalue, Node *aprev, Node *anext):
        value(std::move(avalue)),
        prev(aprev),
        next(anext)
      {}

      template < typename... Args >
      explicit Node(Args &&... args, Node *aprev, Node *anext):
        Node(Node(std::forward< Args >(args)..., aprev, anext))
      {}
    };
  }
}

#endif
