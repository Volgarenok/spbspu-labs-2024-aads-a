#include "list.hpp"

#include <iostream>
#include "node.hpp"

template < class T >
arakelyan::List< T >::List():
  head(nullptr)
{}


template < class T >
bool arakelyan::List< T >::isEmpty() const
{
  return head == nullptr;
}

template < class T >
void arakelyan::List< T >::push_back(const T & el)
{
  Node<T> * node = new Node<T>(el);
  if (isEmpty())
  {
    head = node;
    return;
  }
  Node<T> *current = head;
  while(current->nextPtr)
  {
    current = current->nextPtr;
  }
  current->nextPtr = node;
}

template < class T >
void arakelyan::List< T >::push_front(const T & el)
{
  Node<T> * node = new Node<T>(el);
  node->nextPtr = head;
  head = node;
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
