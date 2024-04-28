#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  namespace detail
  {
    template< typename T >
    class Node
    {
    public:
      Node(const T & value_):
        value(value_),
        prev(nullptr),
        next(nullptr)
      {}
      ~Node() = default;
      T value;
      Node* prev;
      Node* next;
    };
  }
}
#endif
