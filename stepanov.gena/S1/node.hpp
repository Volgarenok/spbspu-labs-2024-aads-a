#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace stepanov
{
  template <typename T>
  struct Node
  {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr){}
    Node(T&& value) : data(std::move(value)), next(nullptr){}
  };
}

#endif
