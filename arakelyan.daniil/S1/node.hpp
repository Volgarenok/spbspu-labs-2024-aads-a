#ifndef NODE_HPP
#define NODE_HPP

namespace arakelyan
{
  namespace details
  {
    template < class T >
    struct Node
    {
      Node() = default;

      Node(const T &val, Node *nextPtr, Node *prevPtr):
        value(val),
        nextNode(nextPtr),
        prevNode(prevPtr)
      {}

      Node(const T &el):
        value(el),
        nextNode(nullptr),
        prevNode(nullptr)
      {}

      Node(const Node &anotherNode) = default;
      ~Node() = default;

      T value;
      Node *nextNode;
      Node *prevNode;
    };
  }
}
#endif
