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

      template < typename... Args >
      explicit Node(Node *aprev, Node *anext, Args &&... args):
        value(std::forward< Args >(args)...),
        prev(aprev),
        next(anext)
      {}
    };
  }
}

#endif
