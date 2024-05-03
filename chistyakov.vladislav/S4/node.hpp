#ifndef NODE_HPP
#define NODE_HPP

namespace chistyakov
{
  template< typename T >
  struct Node
  {
    T value;
    Node * left;
    Node * right:
    Node * parent;
  };
}

#endif
