#ifndef NODE_HPP
#define NODE_HPP

namespace novokhatskiy
{
  template<typename T >
  struct Node
  {
    T value_;
    Node* next_;
    Node(const T& value, Node* next = nullptr) :
      value_(value),
      next_(next)
    {}
  };
}

#endif 
