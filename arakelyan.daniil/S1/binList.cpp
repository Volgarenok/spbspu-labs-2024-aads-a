#include "binList.hpp"

#include <iostream>
#include <stdexcept>
#include "node.hpp"

template < class T >
arakelyan::BinList< T >::BinList():
  head_(nullptr),
  tail_(nullptr),
  size(0)
{}

template < class T >
void arakelyan::BinList< T >::push_back(const T &el)
{
  Node<T> *node = nullptr;
  try
  {
    node = new Node<T>(el);
  }
  catch (...)
  {
    throw std::logic_error("error!");
  }
  node->prevNode = tail_;
  if (tail_ != nullptr)
  {
    tail_->nextNode = node;
  }
  if (head_ == nullptr)
  {
    head_ = node;
  }
  tail_ = node;
  ++size;
}

template < class T >
void arakelyan::BinList< T >::push_front(const T &el)
{
  Node<T> *node = nullptr;
  try
  {
    node = new Node<T>(el);
  }
  catch (...)
  {
    throw std::logic_error("error!");
  }
  node->nextNode = head_;
  if (head_ != nullptr)
  {
    head_->prevNode = node;
  }
  if (tail_ == nullptr)
  {
    tail_ = node;
  }
  head_ = node;
  ++size;
}

template < class T >
void arakelyan::BinList< T >::pop_front()
{
  if (head_ == nullptr)
  {
    return;
  }
  Node< T > *node = head_->nextNode;
  if (node != nullptr)
  {
    node->prevNode = nullptr;
  }
  else
  {
    tail_ = nullptr;
  }
  delete head_;
  head_ = node;
  --size;
}

template < class T >
void arakelyan::BinList< T >::pop_back()
{
  if (tail_ == nullptr)
  {
    return;
  }
  Node< T > *node = tail_->prevNode;
  if (node != nullptr)
  {
    node->nextNode = nullptr;
  }
  else
  {
    head_ = nullptr;
  }
  delete tail_;
  tail_ = node;
  --size;
}

template < class T >
Iterator< T > arakelyan::BinList<T>::begin() const
{
  return Iterator< T >(head_);
}

template < class T >
Iterator< T > arakelyan::BinList<T>::end() const
{
  return Iterator< T >(tail_);
}

template < class T >
void arakelyan::BinList< T >::clear()
{
  if (head_ == nullptr)
  {
    return;
  }
  while (head_ != nullptr)
  {
    pop_front();
  }
}

template < class T >
void arakelyan::BinList< T >::printList(std::ostream &out) const
{
  if (head_ == nullptr)
  {
    return;
  }
  Node<T> *i = head_;
  while (i)
  {
    out << i->value << " -> ";
    i = i->nextNode;
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
