#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template < typename T >
  class Node
  {
  public:
    Node(const T & value):
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
#endif
