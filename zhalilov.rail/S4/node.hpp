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
      Node *right;
      Node *middle;
      T value1;
      T value2;
    };

  }
}

#endif
