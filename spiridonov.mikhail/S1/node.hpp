#ifndef NODE_HPP
#define NODE_HPP

namespace spiridonov
{

  template <typename T>
  struct Node
  {
    T data;
    Node<T>* next;

    Node()
    {}
    Node(T value);
    Node(T value, Node* next);
    Node<T>::Node() : data(T()), next(nullptr)
    {}
    Node<T>::Node(T value) : data(value), next(nullptr)
    {}
    Node<T>::Node(T value, Node* next) : data(value), next(next)
    {}

  };
}

#endif
