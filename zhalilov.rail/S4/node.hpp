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
      Node *left;
      Node *mid;
      Node *right;
      T one;
      T two;
      NodeType type;
    };

  }
}

#endif
