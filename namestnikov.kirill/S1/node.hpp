#ifndef NODE_HPP
#define NODE_HPP

namespace namestnikov
{
  template<class T>
  struct Node
  {
    Node(const T & data = T(), Node * next = nullptr):
      data_(data), next_(next)
    {}
    ~Node() = default;
    T data_;
    Node * next_;
  };
}

#endif
