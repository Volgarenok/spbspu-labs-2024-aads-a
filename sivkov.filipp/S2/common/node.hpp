#ifndef NODE_HPP
#define NODE_HPP

namespace sivkov
{
  template <typename T>
  struct Node
  {
    T data;
    Node* next;
    Node(const T& data_) :
      data(data_),
      next(nullptr)
    {}
  };
}

#endif
