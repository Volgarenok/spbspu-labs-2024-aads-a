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

      explicit Node(const T &el):
        value(el),
        nextNode(nullptr),
        prevNode(nullptr)
      {}

      Node(const Node &anotherNode) = delete;
      ~Node() = default;

      T value;
      Node *nextNode;
      Node *prevNode;
    };
  }
}
#endif
