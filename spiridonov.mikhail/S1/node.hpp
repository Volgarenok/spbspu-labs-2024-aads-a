#ifndef NODE_HPP
#define NODE_HPP
#include <cstddef>

namespace spiridonov
{

  template <typename T>
  struct Node
  {
    T data;
    Node<T>* next;

    Node();
    Node(T value);
    Node(T value, Node* next);
  };

  template <typename T>
  Node<T>::Node(): data(T()), next(nullptr)
  {}

  template <typename T>
  Node<T>::Node(T value): data(value), next(nullptr)
  {}

  template <typename T>
  Node<T>::Node(T value, Node* next): data(value), next(next)
  {}

}

#endif
