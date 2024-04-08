#ifndef NODE_HPP
#define NODE_HPP

namespace zakozhurnikova
{
  namespace detail
  {
    template < typename T >
    struct Node
    {
      T data;
      Node* next;
      Node* prev;
    };
  }
}

#endif
