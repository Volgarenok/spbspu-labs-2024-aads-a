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
      Node(const T & value):
        value_(value),
        prev(nullptr),
        next(nullptr)
      {}
      ~Node() = default;
      T value_;
      Node* prev;
      Node* next;
    };
  }
}
#endif
