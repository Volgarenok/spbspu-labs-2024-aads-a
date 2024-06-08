#ifndef NODE_HPP
#define NODE_HPP

namespace chistyakov
{
  template< typename T >
  struct Node
  {
    Node():
      left(nullptr),
      right(nullptr),
      parent(nullptr)
    {}

    Node(const T & value):
      value(value),
      left(nullptr),
      right(nullptr),
      parent(nullptr)
    {}

    T value;
    Node * left;
    Node * right;
    Node * parent;
  };
}

#endif
