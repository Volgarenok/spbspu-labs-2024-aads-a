#ifndef BINLIST_HPP
#define BINLIST_HPP

#include <cassert>
#include <initializer_list>
#include <memory>
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
    BinList(BinList< T > &&otherLs) noexcept;
    BinList(std::initializer_list< T > otherLs);
    template < class Iterator_t >
    BinList(Iterator_t it_start, Iterator_t it_end);
    ~BinList();

    BinList< T > &operator=(const BinList< T > &otherLs);
    BinList< T > &operator=(BinList< T > &&otherLs) noexcept;
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

    void swap(BinList &ls) noexcept;

    void remove(const T &val);
    template < class Unarypredicate >
    void remove_if(Unarypredicate p);

    iterator insert(const_iterator it_pos, const T &val);

    iterator erase(iterator it_pos);
    iterator erase(iterator it_start, iterator it_end);

    void splice(iterator it_this, BinList< T > &otherLs);
    void splice(const_iterator it_this, std::initializer_list< T > otherLs);
    void splice(const_iterator it_this, BinList< T > &otherLs, const_iterator it_other);

    void reverse() noexcept;

    bool operator==(const BinList< T > &otherLs) const;
    bool operator!=(const BinList< T > &otherLs) const;
    bool operator<(const BinList< T > &otherLs) const;
    bool operator>(const BinList< T > &otherLs) const;
    bool operator<=(const BinList< T > &otherLs) const;
    bool operator>=(const BinList< T > &otherLs) const;

  private:
    template < class Iterator_t >
    void copyFromRange(Iterator_t it_start, Iterator_t it_end);
    using Node = details::Node< T >;
    Node *head_;
    Node *tail_;
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
  if (!otherLs.empty())
  {
    copyFromRange(otherLs.cbegin(), otherLs.cend());
  }
}

template < class T >
arakelyan::BinList< T >::BinList(std::initializer_list< T > otherLs):
  BinList(otherLs.begin(), otherLs.end())
{}

template < class T >
template < class Iterator_t >
arakelyan::BinList< T >::BinList(Iterator_t it_start, Iterator_t it_end):
  BinList()
{
  copyFromRange(it_start, it_end);
}

template < class T >
template < class Iterator_t >
void arakelyan::BinList< T >::copyFromRange(Iterator_t it_start, Iterator_t it_end)
{
  for (auto it = it_start; it != it_end; ++it)
  {
    push_back(*it);
  }
}

template < class T >
arakelyan::BinList< T >::~BinList()
{
  clear();
}

template < class T >
arakelyan::BinList< T > &arakelyan::BinList< T >::operator=(const arakelyan::BinList< T > &otherLs)
{
  BinList< T > tempList(otherLs);
  if (this != std::addressof(tempList))
  {
    swap(tempList);
  }
  return *this;
}

template < class T >
arakelyan::BinList< T > &arakelyan::BinList< T >::operator=(BinList< T > &&otherLs) noexcept
{
  BinList< T > temp(std::move(otherLs));
  if (this != std::addressof(otherLs))
  {
    clear();
    swap(otherLs);
  }
  return *this;
}

template < class T >
arakelyan::BinList< T > &arakelyan::BinList< T >::operator=(std::initializer_list< T > otherLs)
{
  clear();
  copyFromRange(otherLs.begin(), otherLs.end());
  return *this;
}

template < class T >
size_t arakelyan::BinList< T >::get_size() const noexcept
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
T &arakelyan::BinList< T >::front()
{
  assert(!empty());
  return head_->value;
}

template < class T >
T &arakelyan::BinList< T >::back()
{
  assert(!empty());
  return tail_->value;
}

template < class T >
const T &arakelyan::BinList< T >::front() const
{
  assert(!empty());
  return head_->value;
}

template < class T >
const T &arakelyan::BinList< T >::back() const
{
  assert(!empty());
  return tail_->value;
}

template < class T >
void arakelyan::BinList< T >::push_back(const T &el)
{
  details::Node< T > *node = new details::Node< T >(el);
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
  details::Node< T > *node = new details::Node< T >(el);
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
void arakelyan::BinList< T >::pop_front()
{
  assert(!empty());
  details::Node< T > *node = head_->nextNode;
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
  assert(!empty());
  details::Node< T > *node = tail_->prevNode;
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
  for (size_t i = 0; i < size; ++i)
  {
    push_back(val);
  }
}

template < class T >
void arakelyan::BinList< T >::assign(std::initializer_list< T > otherLs)
{
  clear();
  copyFromRange(otherLs.begin(), otherLs.end());
}

template < class T >
void arakelyan::BinList< T >::assign(iterator it_start, iterator it_end)
{
  copyFromRange(it_start, it_end);
}

template < class T >
void arakelyan::BinList< T >::clear() noexcept
{
  while (head_)
  {
    pop_front();
  }
}

template < class T >
void arakelyan::BinList< T >::swap(BinList< T > &otherLs) noexcept
{
  std::swap(head_, otherLs.head_);
  std::swap(tail_, otherLs.tail_);
  std::swap(size_, otherLs.size_);
}

template < class T >
arakelyan::details::Node< T > *delete_node(arakelyan::details::Node< T > *node)
{
  using Node = arakelyan::details::Node< T >;
  Node *prevNode = node->prevNode;
  Node *nextNode = node->nextNode;
  Node *nodeToDel = node;
  delete nodeToDel;
  nextNode->prevNode = prevNode;
  prevNode->nextNode = nextNode;
  return nextNode;
}

template < class T >
void arakelyan::BinList< T >::remove(const T &val)
{
  assert(!empty());
  details::Node< T > *node = head_;
  while (node)
  {
    if (node->value == val)
    {
      if (node == head_)
      {
        pop_front();
        node = head_->nextNode;
      }
      else if (node == tail_)
      {
        pop_back();
        return;
      }
      else
      {
        node = delte_node(node);
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
  details::Node< T > *node = head_;
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
        node = delete_node(node);
      }
    }
    else
    {
      node = node->nextNode;
    }
  }
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::insert(const_iterator it_pos, const T &val)
{
  if (it_pos == cbegin())
  {
    push_front(val);
    return begin();
  }
  else if (it_pos == cend())
  {
    push_back(val);
    return begin();
  }
  else
  {
    details::Node< T > *newNode = new details::Node< T >(val);
    details::Node< T > *nextNode = it_pos.node->nextNode;
    it_pos.node->nextNode = newNode;
    newNode->prevNode = it_pos.node;
    newNode->nextNode = nextNode;
    nextNode->prevNode = newNode;
    ++size_;
    return Iterator< T >(newNode);
  }
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::erase(iterator it_pos)
{
  if (it_pos == begin())
  {
    pop_front();
    return begin();
  }
  else if (it_pos == end() || it_pos.node->nextNode == nullptr)
  {
    pop_back();
    return end();
  }
  else
  {
    details::Node< T > *prevNode = it_pos.node->prevNode;
    details::Node< T > *nextNode = it_pos.node->nextNode;
    prevNode->nextNode = nextNode;
    nextNode->prevNode = prevNode;
    delete it_pos.node;
    return Iterator< T >(nextNode);
  }
}

template < class T >
arakelyan::Iterator< T > arakelyan::BinList< T >::erase(iterator it_start, iterator it_end)
{
  auto st = it_start;
  auto end = it_end;
  while (st != end)
  {
    st = erase(st);
  }
  return st;
}

template < class T >
void arakelyan::BinList< T >::splice(iterator it_this, BinList<T> &otherLs)
{
  assert(!otherLs.empty());
  if (it_this == end())
  {
    tail_->nextNode = otherLs.head_;
    otherLs.head_->prevNode = tail_;
    tail_ = otherLs.tail_;
  }
  else if (it_this == begin())
  {
    auto it = begin();
    ++it;
    head_->nextNode = otherLs.head_;
    otherLs.head_->prevNode = head_;
    otherLs.tail_->nextNode = it.node;
    it.node->prevNode = otherLs.tail_;
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
void arakelyan::BinList< T >::splice(const_iterator it_this, std::initializer_list< T > otherLs)
{
  if (it_this == cend())
  {
    auto it = otherLs.begin();
    while (it != otherLs.end())
    {
      push_back(*it);
      ++it;
    }
  }
  else if (it_this == cbegin())
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
      insert(it, *it_other);
      ++it;
      ++it_other;
    }
  }
}

template < class T >
void arakelyan::BinList< T >::splice(const_iterator it_this, BinList< T > &otherLs, const_iterator it_other)
{
  insert(it_this, *it_other);

  if (it_other == otherLs.cbegin())
  {
    otherLs.pop_front();
  }
  else if (it_other == otherLs.cend())
  {
    otherLs.pop_back();
  }
  else
  {
    details::Node< T > *nodeOtherLs = it_other.node;
    nodeOtherLs->nextNode->prevNode = nodeOtherLs->prevNode;
    nodeOtherLs->prevNode->nextNode = nodeOtherLs->nextNode;
    --otherLs.size_;
  }
}

template < class T >
void arakelyan::BinList< T >::reverse() noexcept
{
  if (empty())
  {
    return;
  }
  details::Node< T > *node = head_;
  node->prevNode = tail_->nextNode;
  node->nextNode->prevNode = node;
  tail_->nextNode = nullptr;
  while (node != nullptr)
  {
    details::Node< T > *tempNode = node->nextNode;
    std::swap(node->prevNode, node->nextNode);
    node = tempNode;
  }
  std::swap(head_, tail_);
}

template < class T >
bool arakelyan::BinList< T >::operator==(const BinList< T > &otherLs) const
{
  if (size_ != otherLs.size_)
  {
    return false;
  }
  auto it = cbegin();
  auto otherIt = otherLs.cbegin();
  while (it != cend() && otherIt != otherLs.cend())
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
  auto it = cbegin();
  auto otherIt = otherLs.cbegin();
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
  return !(*this > otherLs);
}

template < class T >
bool arakelyan::BinList< T >::operator>=(const BinList< T > &otherLs) const
{
  return !(*this < otherLs);
}

#endif
