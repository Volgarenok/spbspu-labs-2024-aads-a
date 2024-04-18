#ifndef NODE_HPP
#define NODE_HPP

namespace zhalilov
{
  namespace detail
  {
    enum class NodeType
    {
      Leaf,
      Two,
      Three
    };

    template < class T >
    struct Node
    {
      Node *parent;
      Node *childs[3];
      Node *next;
      Node *prev;
      T values[2];
      NodeType type;
    };

  }
}

#endif
