#ifndef NODE_HPP
#define NODE_HPP

namespace gladyshev
{
  namespace detail
  {
    template < typename T >
    struct Node
    {
      T data;
      Node* next;
      Node(const T& data_):
        data(data_),
        next(nullptr)
      {}
    };
  }
}

#endif
