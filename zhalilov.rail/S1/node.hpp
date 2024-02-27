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

    Node(T &&newValue, Node *newPrev, Node *newNext):
      value(newValue),
      prev(newPrev),
      next(newNext)
    {}
  };
}

#endif
