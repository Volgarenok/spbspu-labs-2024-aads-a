#ifndef BINLIST_HPP
#define BINLIST_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include "iterator.hpp"
#include "constIterator.hpp"
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList
  {
    using iterator = Iterator< T >;
    using const_iterator =  ConstIterator< T >;

    BinList();
    BinList(const T &val, size_t size);
    BinList(const BinList< T > &otherLs);
    BinList(std::initializer_list< T > otherLs);
    BinList(iterator it_start, iterator it_end);
    ~BinList();

    BinList< T > &operator=(const BinList< T > &otherLs);
    BinList< T > &operator=(BinList< T > &&otherLs);
    BinList< T > &operator=(std::initializer_list< T > otherLs);

    size_t get_size() const noexcept;
    bool empty() const noexcept;

    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator cend() const noexcept;

    T &front();
    T &back();
    const T &front() const;
    const T &back() const;

    void push_back(const T &el);
    void push_front(const T &el);

    void pop_front();
    void pop_back();

    void assign(const T &val, size_t size);
    void assign(iterator it_start, iterator it_end);
    void assign(std::initializer_list< T > otherLs);

    void clear() noexcept;

    void swap(BinList &ls);

    void remove(const T &val);
    template < class Unarypredicate >
    void remove_if(Unarypredicate p);

    iterator insert(const_iterator it_pos, const T &val);

    iterator erase(iterator it_pos);
    iterator erase(iterator it_start, iterator it_end);

    void splice(iterator it_this, BinList< T > &otherLs);
    void splice(iterator it_this, std::initializer_list< T > otherLs);
    void splice(iterator it_this, BinList< T > &otherLs, iterator it_other);

    void reverse() noexcept;

    bool operator==(const BinList< T > &otherLs) const;
    bool operator!=(const BinList< T > &otherLs) const;
    bool operator<(const BinList< T > &otherLs) const;
    bool operator>(const BinList< T > &otherLs) const;
    bool operator<=(const BinList< T > &otherLs) const;
    bool operator>=(const BinList< T > &otherLs) const;

  private:
    Node< T > *head_;
    Node< T > *tail_;
    size_t size_;
  };
}

template < class T >
arakelyan::BinList< T >::BinList():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
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
arakelyan::BinList< T >::BinList(const BinList<T> &otherLs):
  BinList()
{
  auto it = otherLs.cbegin();
  while (size_ != otherLs.size_)
  {
    push_back(*it);
    ++it;
  }
}

template < class T >
arakelyan::BinList< T >::BinList(std::initializer_list< T > otherLs)
{
  for (auto it = otherLs.begin(); it != otherLs.end(); ++it)
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
size_t arakelyan::BinList< T >::get_size() const
{
  return size_;
}

template < class T >
bool arakelyan::BinList< T >::empty() const noexcept
{
  return head_ == nullptr;
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::begin() noexcept
{
  return Iterator< T >(head_);
}

template < class T >
arakelyan::ConstIterator< T > arakelyan::BinList< T >::cbegin() const noexcept
{
  return ConstIterator< T >(head_);
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::end() noexcept
{
  return Iterator< T >(tail_->nextNode);
}

template < class T >
arakelyan::ConstIterator< T > arakelyan::BinList< T >::cend() const noexcept
{
  return ConstIterator< T >(tail_->nextNode);
}

template < class T >
void arakelyan::BinList< T >::splice(iterator it_this, BinList<T> &otherLs)
{
  assert(!otherLs.empty());
  if (it_this == end())
  {
    auto it = otherLs.begin();
    while (it != otherLs.end())
    {
      push_back(*it);
      ++it;
    }
  }
  else if (it_this == begin())
  {
    auto it = otherLs.begin();
    while (it != otherLs.end())
    {
      push_front(*it);
      ++it;
    }
  }
  else
  {
    auto it = it_this;
    auto it_next = ++it;
    otherLs.head_->prevNode = it_this.node;
    it_this.node->nextNode = otherLs.head_;
    otherLs.tail_->nextNode = it_next.node;
    if (it_next != end())
    {
      it_next.node->prevNode = otherLs.tail_;
    }
    else
    {
      tail_ = otherLs.tail_;
    }
    size_ += otherLs.size_;
  }
  otherLs.head_ = nullptr;
  otherLs.tail_ = nullptr;
}

template < class T >
void arakelyan::BinList< T >::splice(iterator it_this, std::initializer_list< T > otherLs)
{
  if (it_this == end())
  {
    auto it = otherLs.begin();
    while (it != otherLs.end())
    {
      push_back(*it);
      ++it;
    }
  }
  else if (it_this == begin())
  {
    auto it = otherLs.end();
    --it;
    while (it != otherLs.begin())
    {
      push_front(*it);
      --it;
    }
    push_front(*it);
  }
  else
  {
    auto it = it_this;
    auto it_other = otherLs.begin();
    while (it_other != otherLs.end())
    {
      insert_after(it, *it_other);
      ++it;
      ++it_other;
    }
  }
}

template < class T >
void arakelyan::BinList< T >::splice(iterator it_this, BinList< T > &otherLs, iterator it_other) //ne to
{
  if (it_this == begin())
  {
    push_front(*it_other);
    otherLs.erase(it_other);
  }
  else if (it_this == end())
  {
    push_back(*it_other);
    otherLs.erase(it_other);
  }
  else
  {
    insert_after(it_this, *it_other);
    otherLs.erase(it_other);
  }
}

// template < class T >
// void arakelyan::BinList< T >::reverse() noexcept
// {
//
// }

template < class T >
T &arakelyan::BinList< T >::front()
{
  return head_->value;
}

template < class T >
T &arakelyan::BinList< T >::back()
{
  return tail_->value;
}

template < class T >
const T &arakelyan::BinList< T >::front() const
{
  return head_->value;
}

template < class T >
const T &arakelyan::BinList< T >::back() const
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
arakelyan::Iterator< T > arakelyan::BinList< T >::insert(const_iterator it_pos, const T &val)
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
    auto it = begin();
    Node< T > *prevNode = head_;
    while (it != it_pos)
    {
      ++it;
      prevNode = prevNode->nextNode;
    }
    Node< T > *newNode = new Node< T >(val);
    Node< T > *nextNode = prevNode->nextNode;
    prevNode->nextNode = newNode;
    newNode->prevNode = prevNode;
    newNode->nextNode = nextNode;
    nextNode->prevNode = newNode;
    ++size_;
    return Iterator< T >(newNode);
  }
}

template < class T >
void arakelyan::BinList< T >::clear() noexcept
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
void arakelyan::BinList< T >::remove(const T &val)
{
  Node< T > *node = head_;
  while (node)
  {
    if (node->value == val)
    {
      if (node == head_)
      {
        pop_front();
      }
      else if (node == tail_)
      {
        pop_back();
      }
      else
      {
        Node< T > *prevNode = node->prevNode;
        Node< T > *nextNode = node->nextNode;
        Node< T > *nodeToDel = node;
        delete nodeToDel;
        node = nextNode;
        nextNode->prevNode = prevNode;
        prevNode->nextNode = nextNode;
      }
    }
    else
    {
      node = node->nextNode;
    }
  }
}

template < class T >
template < class UnaryPredicate >
void arakelyan::BinList< T >::remove_if(UnaryPredicate p)
{
  Node< T > *node = head_;
  while (node)
  {
    if (p(node->value))
    {
      if (node == head_)
      {
        pop_front();
      }
      else if (node == tail_)
      {
        pop_back();
      }
      else
      {
        Node< T > *prevNode = node->prevNode;
        Node< T > *nextNode = node->nextNode;
        Node< T > *nodeToDel = node;
        delete nodeToDel;
        node = nextNode;
        nextNode->prevNode = prevNode;
        prevNode->nextNode = nextNode;
      }
    }
    else
    {
      node = node->nextNode;
    }
  }
}

template < class T >
void arakelyan::BinList< T >::swap(BinList< T > &otherLs)
{
  std::swap(head_, otherLs.head_);
  std::swap(tail_, otherLs.tail_);
  std::swap(size_, otherLs.size_);
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::erase(iterator it_pos)
{
  Node< T > *nodeToDel = head_;
  if (it_pos == begin())
  {
    pop_front();
    return begin();
  }
  else if (it_pos == end())
  {
    pop_back();
    return end();
  }
  else
  {
    auto it = begin();
    while (it != it_pos)
    {
      ++it;
      nodeToDel = nodeToDel->nextNode;
    }
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
      erase(it_start);
    }
    return it_start;
  }
  while (it_start != it_end && it_start != end())
  {
    erase(it_start);
  }
  return it_end;
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
void arakelyan::BinList< T >::assign(std::initializer_list< T > otherLs)
{
  clear();
  head_ = nullptr;
  tail_ = nullptr;
  for (auto it = otherLs.begin(); it != otherLs.end(); ++it)
  {
    push_back(*it);
  }
}

template < class T >
void arakelyan::BinList< T >::assign(iterator it_start, iterator it_end)
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
arakelyan::BinList< T > &arakelyan::BinList< T >::operator=(const arakelyan::BinList< T > &otherLs)
{
  if (this != &otherLs)
  {
    clear();
    const auto otherIt = otherLs.cbegin();
    while (otherIt != otherLs.cend())
    {
      push_back(*otherIt);
      ++otherIt;
    }
  }
  return *this;
}

template < class T >
arakelyan::BinList< T > &arakelyan::BinList< T >::operator=(BinList< T > &&otherLs)
{
  if (this != &otherLs)
  {
    clear();
    swap(std::move(otherLs));
  }
  return *this;
}

template < class T >
arakelyan::BinList< T > &arakelyan::BinList< T >::operator=(std::initializer_list< T > otherLs)
{
  clear();
  auto otherIt = otherLs.begin();
  while (otherIt != otherLs.end())
  {
    push_back(*otherIt++);
  }
  return *this;
}

template < class T >
bool arakelyan::BinList< T >::operator==(const BinList< T > &otherLs) const
{
  if (size_ != otherLs.size_)
  {
    return false;
  }
  auto it = begin();
  auto otherIt = otherLs.begin();
  while (it != end() && otherIt != otherLs.end())
  {
    if (*it != *otherIt)
    {
      return false;
    }
    ++it;
    ++otherIt;
  }
  return true;
}

template < class T >
bool arakelyan::BinList< T >::operator!=(const BinList< T > &otherLs) const
{
  return !(*this == otherLs);
}

template < class T >
bool arakelyan::BinList< T >::operator<(const BinList< T > &otherLs) const
{
  const auto it = cbegin();
  const auto otherIt = otherLs.cbegin();
  while (it != cend() && otherIt != otherLs.cend())
  {
    if (*it < *otherIt)
    {
      return true;
    }
    else if (*it > *otherIt)
    {
      return false;
    }
    ++it;
    ++otherIt;
  }
  return (it == cend() && otherIt != otherLs.cend());
}

template < class T >
bool arakelyan::BinList< T >::operator>(const BinList< T > &otherLs) const
{
  return !(*this < otherLs);
}

template < class T >
bool arakelyan::BinList< T >::operator<=(const BinList< T > &otherLs) const
{
  return (*this < otherLs || *this == otherLs);
}

template < class T >
bool arakelyan::BinList< T >::operator>=(const BinList< T > &otherLs) const
{
  return !(*this < otherLs || *this == otherLs);
}

template < class T >
arakelyan::BinList< T >::~BinList()
{
  clear();
}

#endif
