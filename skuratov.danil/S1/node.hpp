#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template < typename T >
  class Node
  {
  public:
    Node():
      prev(nullptr),
      next(nullptr)
    {}
    Node(T value):
      value(value),
      prev(nullptr),
      next(nullptr)
    {}
    ~Node() = default;
    T value;
    Node* prev;
    Node* next;
  };
}
#endif
