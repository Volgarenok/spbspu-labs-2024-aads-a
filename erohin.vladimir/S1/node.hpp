#ifndef NODE_HPP
#define NODE_HPP

namespace erohin
{
  template< class T >
  struct Node
  {
    T data_;
    Node * next_;
  };
}

#endif
