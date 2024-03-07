#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace zhalilov
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

    Node(const T &newValue):
      value(newValue),
      prev(nullptr),
      next(nullptr)
    {}

    Node(T &&newValue):
      value(std::move(newValue)),
      prev(nullptr),
      next(nullptr)
    {}
  };
}

#endif
