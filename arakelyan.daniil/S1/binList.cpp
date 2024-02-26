#include "binList.hpp"

#include <iostream>
#include <stdexcept>
#include "node.hpp"

template < class T >
arakelyan::BinList< T >::BinList():
  head_(nullptr),
  tail_(nullptr)
{}

template < class T >
bool arakelyan::BinList< T >::isEmpty() const
{
  return head_ == nullptr;
}

template < class T >
void arakelyan::BinList< T >::push_back(const T & el)
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
    head_ = node;
  }
  if (tail_ != nullptr)
  {
    tail_->nextPtr = node;
  }
  tail_ = node;
}

template < class T >
void arakelyan::BinList< T >::push_front(const T & el)
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
  node->nextPtr = head_;
  head_ = node;
  if (tail_ == nullptr)
  {
    tail_ = node;
  }
}

template < class T >
void arakelyan::BinList< T >::pop_front()
{
  if (isEmpty())
  {
    return;
  }
  if (head_ == tail_)
  {
    delete tail_;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  Node<T> * node = head_;
  head_ = node->nextPtr;
  delete node;
}

template < class T >
void arakelyan::BinList< T >::pop_back()
{
  if (tail_ == nullptr)
  {
    return;
  }
  if (head_ == tail_)
  {
    delete tail_;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  Node<T> * noda = head_;
  for (; noda->nextPtr != tail_; noda = noda->nextPtr);
  noda->nextPtr = nullptr;
  delete tail_;
  tail_ = noda;
}

template < class T >
void arakelyan::BinList< T >::clear()
{
  if (isEmpty())
  {
    return;
  }
  while (head_ != nullptr)
  {
    pop_front();
  }
}

template < class T >
void arakelyan::BinList< T >::printList(std::ostream & out) const
{
  if (isEmpty())
  {
    return;
  }
  Node<T> * i = head_;
  while (i)
  {
    out << i->value << " -> ";
    i = i->nextPtr;
  }
  out << "end";
}

template < class T >
arakelyan::BinList< T >::~BinList()
{
  while (head_ != nullptr)
  {
    pop_front();
  }
}
