#ifndef NODE_HPP
#define NODE_HPP

namespace chistyakov
{
  namespace detail
  {
    template< typename T >
    struct Node
    {
      Node(const T & value):
        value(value),
        next(nullptr),
        previous(nullptr)
      {}

      ~Node() = default;

      T value;
      Node * next;
      Node * previous;
    };
  }
}

#endif
