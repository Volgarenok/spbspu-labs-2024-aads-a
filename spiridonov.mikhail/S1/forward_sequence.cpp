#include "forward_sequence.hpp"
#include <cstring>

namespace spiridonov
{

  template <typename T>
  Sequence<T>::Sequence() : head(nullptr), tail(nullptr), size(0)
  {
  }

  template <typename T>
  Sequence<T>::~Sequence()
  {
    while (head != nullptr)
    {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
  }

  template <typename T>
  void Sequence<T>::push_back(T value)
  {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
    size++;
  }

  template <typename T>
  typename Sequence<T>::Iterator Sequence<T>::begin()
  {
    return Iterator(head);
  }

  template <typename T>
  typename Sequence<T>::Iterator Sequence<T>::end()
  {
    return Iterator(nullptr);
  }

}

