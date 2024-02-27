#ifndef NODE_HPP
#define NODE_HPP

template < class T >
struct Node
{
  T value;
  Node * nextNode;
  Node * prevNode;

  Node();
  ~Node() = default;
  Node(const T& val);
};

#endif
