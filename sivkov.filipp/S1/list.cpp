#include "list.hpp"
#include <stdexcept>

template<typename T>
List<T>::List()
{
  size = 0;
  head = nullptr;
}

template<typename T>
List<T>::~List()
{
}

template<typename T>
void List<T>::push_back(T data)
{
  if (head == nullptr)
  {
    head = new Node(data);
  }
  else
  {
    Node* current = this->head;
    while (current->pNext != nullptr)
    {
      current = current->pNext;
    }
    current->pNext = new Node(data);
  }
  size++;
}

template<typename T>
void List<T>::delete_front()
{
  if (head != nullptr)
  {
    Node* temp = head;
    head = head->pNext;
    delete temp;
    size--;
  }
}

template<typename T>
T& List<T>::operator[](const int index)
{
  int counter = 0;
  Node* current = this->head;
  if (size <= index || index < 0)
  {
    throw std::out_of_range("Index out of range");
  }
  while (current != nullptr)
  {
    if (counter == index)
    {
      return current->data;
    }
    current = current->pNext;
    counter++;
  }
  throw std::logic_error("Index not found");
}
