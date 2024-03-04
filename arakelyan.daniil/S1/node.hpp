#ifndef NODE_HPP
#define NODE_HPP

template < class T >
struct Node
{
  Node();
  Node(const T &val, Node< T > *next, Node< T > *prev);
  Node(const T &val);
  ~Node() = default;

  T value;
  Node *nextNode;
  Node *prevNode;
};

#endif
