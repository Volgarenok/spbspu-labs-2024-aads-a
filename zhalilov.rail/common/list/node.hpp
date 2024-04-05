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
      explicit Node(Args &&... args, Node< T > *prev, Node< T > *next):
        value(std::forward< Args >(args)...),
        prev(prev),
        next(next)
      {}
    };
  }
}

#endif
