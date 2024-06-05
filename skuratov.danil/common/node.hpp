#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  namespace detail
  {
    template< typename T >
    struct Node
    {
      Node(const T& value):
        value_(value),
        prev_(nullptr),
        next_(nullptr)
      {}
      ~Node() = default;
      T value_;
      Node* prev_;
      Node* next_;
    };
  }
}
#endif
