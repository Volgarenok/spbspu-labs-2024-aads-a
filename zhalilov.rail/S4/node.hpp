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

    struct BaseNode
    {
      BaseNode *parent;
      BaseNode *left;
      BaseNode *right;
      NodeType type;
    };

    template < class T >
    struct TwoNode: BaseNode
    {
      T value;
    };

    template < class T >
    struct ThreeNode: BaseNode
    {
      BaseNode *middle;
      T value1;
      T value2;
    };

  }
}

#endif
