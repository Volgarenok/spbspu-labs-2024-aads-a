#ifndef NODE_HPP
#define NODE_HPP

namespace isaychev
{
  template < typename T >
  struct node_t
  {
    T data;
    node_t< T > * next;

    node_t(const T & obj):
      data(obj),
      next(nullptr)
    {}

    node_t(const node_t< T > & rhs):
      data(rhs.data),
      next(nullptr)
    {}
  };
}

#endif
