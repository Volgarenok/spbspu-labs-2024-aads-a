#ifndef NODE_HPP
#define NODE_HPP

namespace isaychev
{
  namespace detail
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
    };
  }
}

#endif
