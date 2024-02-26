#ifndef NODE_HPP
#define NODE_HPP

template < class T >
struct Node
{
  T value;
  Node * nextPtr;

  Node();
  ~Node() = default;
  Node(const T& val);
};

#endif
