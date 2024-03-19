#ifndef NODE_HPP
#define NODE_HPP

namespace lebedev
{
  template< class T >
  struct Node
  {
    Node(const T & data, Node * next = nullptr, Node * prev = nullptr) :
      data_(data),
      next_(next),
      prev_(prev)
    {}
    ~Node() = default;
    T data_;
    Node * next_;
    Node * prev_;
  };
}

#endif
