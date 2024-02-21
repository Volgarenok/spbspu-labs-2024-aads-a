#include "list.h"

template< typename T >
List< T >::List(): head(nullptr), tail(nullptr) {}

template< typename T >
List< T >::List(size_t count, const T & value): head(nullptr), tail(nullptr)
{
  for (size_t i = 0; i < count; ++i)
  {
    push_back(value);
  }
}

template< typename T >
List< T >::List(const std::initializer_list< T > & ilist): head(nullptr), tail(nullptr)
{
  for (const T & value: ilist)
  {
    push_back(value);
  }
}

template< typename T >
List< T >::~List()
{
  while (head)
  {
      Node * temp = head;
      head = head->next;
      delete temp;
  }
}

template< typename T >
bool List< T >::empty() const
{
  return head == nullptr;
}

template< typename T >
void List< T >::push_back(T value)
{
  Node * newNode = new Node(value);
  if (!head)
  {
    head = tail = newNode;
  }
  else
  {
    tail->next = newNode;
    tail = newNode;
  }
}

template< typename T >
void List< T >::push_front(T value)
{
  Node * newNode = new Node(value);
  if (!head)
  {
    head = tail = newNode;
  }
  else
  {
    newNode->next = head;
    head = newNode;
  }
}

template< typename T >
void List< T >::pop_back()
{
  if (!head)
  {
    throw std::out_of_range("List is empty");
  }
  else if (head == tail)
  {
    delete head;
    head = tail = nullptr;
  }
  else
  {
    Node * current = head;
    while (current->next != tail)
    {
      current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
  }
}

template< typename T >
void List< T >::pop_front()
{
  if (!head)
  {
    throw std::out_of_range("List is empty");
  }
  else
  {
    Node * temp = head;
    head = head->next;
    delete temp;
    if (!head)
    {
      tail = nullptr;
    }
  }
}

template< typename T >
void List< T >::insert(size_t index, T value)
{
  if (index == 0)
  {
    push_front(value);
  }
  else
  {
    Node * newNode = new Node(value);
    Node * current = head;
    for (size_t i = 0; i < index - 1; ++i)
    {
      if (!current)
      {
        throw std::out_of_range("Index out of range");
      }
      current = current->next;
    }
    if (!current)
    {
      throw std::out_of_range("Index out of range");
    }
    newNode->next = current->next;
    current->next = newNode;
    if (!newNode->next)
    {
      tail = newNode;
    }
  }
}

template< typename T >
void List< T >::erase(size_t index)
{
  if (index == 0)
  {
    pop_front();
  }
  else
  {
    Node * current = head;
    for (size_t i = 0; i < index - 1; ++i)
    {
      if (!current)
      {
        throw std::out_of_range("Index out of range");
      }
      current = current->next;
    }
    if (!current || !current->next)
    {
      throw std::out_of_range("Index out of range");
    }
    Node * temp = current->next;
    current->next = current->next->next;
    delete temp;
    if (!current->next)
    {
      tail = current;
    }
  }
}

template< typename T >
void List< T >::remove(T value)
{
  while (head && head->value == value)
  {
    Node * temp = head;
    head = head->next;
    delete temp;
  }
  if (!head)
  {
    tail = nullptr;
  }
  else
  {
    Node * current = head;
    while (current->next)
    {
      if (current->next->value == value)
      {
        Node * temp = current->next;
        current->next = current->next->next;
        delete temp;
        if (!current->next)
        {
          tail = current;
        }
      }
      else
      {
        current = current->next;
      }
    }
  }
}

template< typename T >
T & List< T >::at(size_t index) const
{
  Node * current = head;
  for (size_t i = 0; i < index; ++i)
  {
    if (!current)
    {
      throw std::out_of_range("Index out of range");
    }
    current = current->next;
  }
  if (!current)
  {
    throw std::out_of_range("Index out of range");
  }
  return current->value;
}

template< typename T >
size_t List< T >::size() const
{
  size_t count = 0;
  Node * current = head;
  while (current)
  {
    ++count;
    current = current->next;
  }
  return count;
}

template< typename T >
bool List< T >::operator==(const List< T >& other) const
{
  Node * current1 = head;
  Node * current2 = other.head;
  while (current1 && current2)
  {
    if (current1->value != current2->value)
    {
      return false;
    }
    current1 = current1->next;
    current2 = current2->next;
  }
  return !current1 && !current2;
}

template< typename T >
bool List< T >::operator!=(const List< T >& other) const
{
  return !(* this == other);
}

template< typename T >
bool List< T >::operator<(const List< T >& other) const
{
  Node * current1 = head;
  Node * current2 = other.head;
  while (current1 && current2)
  {
    if (current1->value != current2->value)
    {
      return current1->value < current2->value;
    }
    current1 = current1->next;
    current2 = current2->next;
    }
  return (bool)current2;
}

template< typename T >
bool List< T >::operator<=(const List< T >& other) const
{
  return * this < other || * this == other;
}

template< typename T >
bool List< T >::operator>(const List< T >& other) const
{
  return !(* this <= other);
}

template< typename T >
bool List< T >::operator>=(const List< T >& other) const
{
  return * this > other || * this == other;
}

template class List< int >;
