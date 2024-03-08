#include "binList.hpp"

#include <exception>
#include <iostream>
#include <queue>
#include <stdexcept>
#include "iterator.hpp"
#include "node.hpp"

using iterator = arakelyan::Iterator< class T >;

template < class T >
arakelyan::BinList< T >::BinList():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{}

template < class T >
arakelyan::BinList< T >::BinList(Node< T > *head, Node< T > *tail):
  head_(head),
  tail_(tail)
{}

template < class T >
arakelyan::BinList< T >::BinList(const T &val, size_t size):
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
arakelyan::BinList< T >::BinList(std::initializer_list< T > ls)
{
  for (auto it = ls.begin(); it != ls.end(); ++it)
  {
    push_back(*it);
  }
}

template < class T >
arakelyan::BinList< T >::BinList(iterator it_start, iterator it_end)
{
  for (; it_start != it_end; ++it_start)
  {
    push_back(*it_start);
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
arakelyan::Iterator< T > arakelyan::BinList< T >::begin() const
{
  return Iterator< T >(head_);
}

template < class T >
const arakelyan::Iterator< T > arakelyan::BinList< T >::cbegin() const
{
  return Iterator< T >(head_);
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::end() const
{
  return Iterator< T >(tail_->nextNode);
}

template < class T >
const arakelyan::Iterator< T > arakelyan::BinList< T >::cend() const
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
  Node< T > *node = new Node< T >(el);
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
  Node< T > *node = new Node< T >(el);

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
arakelyan::Iterator< T > arakelyan::BinList< T >::insert_after(iterator it_pos, const T &val)
{
  if (it_pos == begin())
  {
    push_front(val);
    return begin();
  }
  else if (it_pos == end())
  {
    push_back(val);
    return begin();
  }
  else
  {
    Node< T > *node = new Node< T >(val);
    Node< T > *nextNode = it_pos->node->nextNode;
    it_pos->node->nextNode = node;
    node->nextNode = nextNode;
    node->prevNode = it_pos->node;
    return Iterator< T >(node);
  }
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
void arakelyan::BinList< T >::swap(BinList<T> &ls)
{
  std::swap(head_, ls.head_);
  std::swap(tail_, ls.tail_);
  std::swap(size_, ls.size_);
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::erase(iterator it_pos)
{
  Node< T > *nodeToDel = it_pos->node;
  if (nodeToDel == begin())
  {
    pop_front();
    return begin();
  }
  else if (nodeToDel == end())
  {
    pop_back();
    return end();
  }
  else
  {
    Node< T > *prevNode = nodeToDel->prevNode;
    Node< T > *nextNode = nodeToDel->nextNode;
    prevNode->nextNode = nextNode;
    nextNode->prevNode = prevNode;
    delete nodeToDel;
    return Iterator< T >(nextNode);
  }
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::erase(iterator it_start, iterator it_end)
{
  if (it_start == begin() && it_end == end())
  {
    clear();
    return end();
  }
  else if (it_start == begin() && it_end != end())
  {
    while (it_start != it_end && it_start != end())
    {
      ++it_start;
      pop_front();
    }
    return it_start;
  }
  else if (it_start != begin() && it_end == end())
  {
    while (it_start != it_end)
    {
      it_start = erase(it_start);
    }
    return it_start;
  }
  while (it_start != it_end && it_start != end())
  {
    it_start = erase(it_start);
  }
}

template < class T >
void arakelyan::BinList< T >::assign(const T &val, const size_t size)
{
  try
  {
    clear();
    head_ = nullptr;
    tail_ = nullptr;
    for (size_t i = 0; i < size; ++i)
    {
      push_back(val);
    }
  }
  catch (const std::exception & e)
  {
    clear();
    throw;
  }
}

template < class T >
void arakelyan::BinList< T >::assign(std::initializer_list< T > ls)
{
  try
  {
    clear();
    head_ = nullptr;
    tail_ = nullptr;
    for (auto it = ls.begin(); it != ls.end(); ++it)
    {
      push_back(*it);
    }
  }
  catch (const std::exception & e)
  {
    clear();
    throw;
  }
}

template < class T >
void arakelyan::BinList< T >::assign(Iterator< T > it_start, Iterator< T > it_end)
{
  try
  {
    clear();
    head_ = nullptr;
    tail_ = nullptr;
    for (auto it = it_start; it != it_end; ++it)
    {
      push_back(*it);
    }
  }
  catch (const std::exception & e)
  {
    clear();
    throw;
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
