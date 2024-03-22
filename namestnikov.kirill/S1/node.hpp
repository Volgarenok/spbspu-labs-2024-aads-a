#ifndef NODE_HPP
#define NODE_HPP

namespace namestnikov
{
  template<class T>
  struct Node
  {
    Node() = default;
    Node(const T & data):
      data_(data), next_(nullptr)
    {}
    ~Node() = default;
    T data_;
    Node * next_;
  };
}

#endif
