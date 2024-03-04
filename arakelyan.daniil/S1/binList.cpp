#include "binList.hpp"

#include <__config>
#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "node.hpp"

template < class T >
arakelyan::BinList< T >::BinList():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{}

template < class T >
arakelyan::BinList< T >::BinList(size_t size, const T &val):
  BinList()
{
  for (size_t i = 0; i < size; ++i)
  {
    push_back(val);
  }
}

template < class T >
arakelyan::BinList< T >::BinList(const BinList<T> &ls):
  BinList()
{
  Node< T > * node = ls.head_;
  while (size_ != ls.size_)
  {
    push_back(node->value);
    node = node->nextNode;
  }
}

template < class T >
size_t arakelyan::BinList< T >::getSize() const
{
  return size_;
}

template < class T >
bool arakelyan::BinList< T >::isEmpty() const
{
  return head_ == nullptr;
}

template < class T >
Iterator< T > arakelyan::BinList< T >::begin() const
{
  return Iterator< T >(head_);
}

template < class T >
const Iterator< T > arakelyan::BinList< T >::cbegin() const
{
  return Iterator< T >(head_);
}

template < class T >
Iterator< T > arakelyan::BinList< T >::end() const
{
  return Iterator< T >(tail_->nextNode);
}

template < class T >
const Iterator< T > arakelyan::BinList< T >::cend() const
{
  return Iterator< T >(tail_->nextNode);
}

template < class T >
T arakelyan::BinList< T >::getFirst() const
{
  return head_->value;
}

template < class T >
T arakelyan::BinList< T >::getLast() const
{
  return tail_->value;
}

template < class T >
void arakelyan::BinList< T >::push_back(const T &el)
{
  Node< T > *node = nullptr;
  try
  {
    node = new Node< T >(el);
  }
  catch (...)
  {
    throw std::logic_error("error!");
  }
  if ((head_ == nullptr) && (tail_ == nullptr))
  {
    head_ = node;
    tail_ = node;
  }
  else
  {
    tail_->nextNode = node;
    node->prevNode = tail_;
    tail_ = node;
  }
  ++size_;
}

template < class T >
void arakelyan::BinList< T >::push_front(const T &el)
{
  Node< T > *node = nullptr;
  try
  {
    node = new Node< T >(el);
  }
  catch (...)
  {
    throw std::logic_error("error!");
  }
  node->nextNode = head_;
  if (head_ == nullptr && tail_ == nullptr)
  {
    head_ = node;
    tail_ = node;
  }
  head_ = node;
  ++size_;
}

template < class T >
void arakelyan::BinList< T >::clear()
{
  while (head_)
  {
    pop_front();
  }
  tail_ = nullptr;
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
  --size_;
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
  --size_;
}


template < class T >
void arakelyan::BinList< T >::assign(const T &val, const size_t size)
{
  clear();
  head_ = nullptr;
  tail_ = nullptr;
  for (size_t i = 0; i < size; ++i)
  {
    push_back(val);
  }
}

template < class T >
void arakelyan::BinList< T >::assign(std::initializer_list< T > ls)
{
  clear();
  head_ = nullptr;
  tail_ = nullptr;
  for (auto it = ls.begin(); it != ls.end(); ++it)
  {
    push_back(*it);
  }
}

template < class T >
void arakelyan::BinList< T >::assign(Iterator< T > it_start, Iterator< T > it_end)
{
  clear();
  head_ = nullptr;
  tail_ = nullptr;
  for (auto it = it_start; it != it_end; ++it)
  {
    push_back(*it);
  }
}

template < class T >
void arakelyan::BinList< T >::printList(std::ostream &out) const
{
  if (head_ == nullptr)
  {
    return;
  }
  Node< T > *i = head_;
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
  clear();
}
