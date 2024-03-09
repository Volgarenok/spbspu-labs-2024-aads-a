#ifndef NODE_HPP
#define NODE_HPP

namespace spiridonov
{

  template <typename T>
  class Node
  {
  public:
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr)
    {
    }
  };

}

#endif
