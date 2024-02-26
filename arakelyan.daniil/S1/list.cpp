#include "list.hpp"

#include <iostream>
#include <stdexcept>
#include "node.hpp"

template < class T >
arakelyan::List< T >::List():
  head(nullptr),
  tail(nullptr)
{}

template < class T >
bool arakelyan::List< T >::isEmpty() const
{
  return head == nullptr;
}

template < class T >
void arakelyan::List< T >::push_back(const T & el)
{
  Node<T> * node = nullptr;
  try
  {
    node = new Node<T>(el);
  }
  catch (...)
  {
    throw std::logic_error("error!");
  }
  if (isEmpty())
  {
    head = node;
  }
  if (tail != nullptr)
  {
    tail->nextPtr = node;
  }
  tail = node;
}

template < class T >
void arakelyan::List< T >::push_front(const T & el)
{
  Node<T> * node = nullptr;
  try
  {
    node = new Node<T>(el);
  }
  catch (...)
  {
    throw std::logic_error("error!");
  }
  node->nextPtr = head;
  head = node;
  if (tail == nullptr)
  {
    tail = node;
  }
}

template < class T >
void arakelyan::List< T >::pop_front()
{
  if (isEmpty())
  {
    return;
  }
  if (head == tail)
  {
    delete tail;
    head = nullptr;
    tail = nullptr;
    return;
  }
  Node<T> * node = head;
  head = node->nextPtr;
  delete node;
}

template < class T >
void arakelyan::List< T >::pop_back()
{
  if (tail == nullptr)
  {
    return;
  }
  if (head == tail)
  {
    delete tail;
    head = nullptr;
    tail = nullptr;
    return;
  }
  Node<T> * noda = head;
  for (; noda->nextPtr != tail; noda = noda->nextPtr);
  noda->nextPtr = nullptr;
  delete tail;
  tail = noda;
}

template < class T >
void arakelyan::List< T >::clear()
{
  if (isEmpty())
  {
    return;
  }
  while (head != nullptr)
  {
    pop_front();
  }
}

template < class T >
void arakelyan::List< T >::printList(std::ostream & out) const
{
  if (isEmpty())
  {
    return;
  }
  Node<T> * i = head;
  while (i)
  {
    out << i->value << " -> ";
    i = i->nextPtr;
  }
  out << "end";
}

template < class T >
arakelyan::List< T >::~List()
{
  while (head != nullptr)
  {
    pop_front();
  }
}
