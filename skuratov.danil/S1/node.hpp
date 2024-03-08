#ifndef NODE_HPP
#define NODE_HPP

namespace skuratov
{
  template <typename T>
  class Node
  {
    Node<T>* prev;
    Node<T>* next;
    T data;

    Node(const T& value):
      data(value),
      prev(nullptr),
      next(nullptr)
    {}
    ~Node() = default;
  };
}
#endif
