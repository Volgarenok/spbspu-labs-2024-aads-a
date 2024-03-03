#ifndef NODE_HPP
#define NODE_HPP

namespace isaychev
{
  template < typename T >
  struct node_t
  {
    T data;
    node_t< T > * next;
  };
}

#endif
