#ifndef NODE_HPP
#define NODE_HPP
namespace sakovskaia
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
#endif
