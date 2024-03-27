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

      Node():
        value(T()),
        prev(nullptr),
        next(nullptr)
      {}

      explicit Node(const T &newValue, Node< T > *prev = nullptr, Node< T > *next = nullptr):
        value(newValue),
        prev(prev),
        next(next)
      {}

      explicit Node(T &&newValue, Node< T > *prev = nullptr, Node< T > *next = nullptr):
        value(std::move(newValue)),
        prev(prev),
        next(next)
      {}

      template < typename... Args >
      explicit Node(Args &&... args, Node< T > *prev = nullptr, Node< T > *next = nullptr):
        value(std::forward< Args >(args)...),
        prev(nullptr),
        next(nullptr)
      {}
    };
  }
}

#endif
