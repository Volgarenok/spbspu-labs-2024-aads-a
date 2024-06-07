#ifndef NODE_HPP
#define NODE_HPP

namespace lopatina
{
  template<typename T>
  struct Node
  {
    T data;
    Node<T> * next;

    Node(T _data):
      data(_data),
      next(nullptr)
    {}
  };
}

#endif
