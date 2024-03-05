#ifndef NODE_HPP
#define NODE_HPP

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
  };
}

#endif
