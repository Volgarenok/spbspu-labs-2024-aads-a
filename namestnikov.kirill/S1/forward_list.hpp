#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "node.hpp"
#include "iterators.hpp"

namespace namestnikov
{
  template <class T>
  class ForwardList
  {
   using node_t = Node<T>;
  public:
    ForwardList():
      head_(nullptr),
      size_(0)
    {}
    ForwardList(size_t size, const T & value):
      head_(nullptr),
      size_(0)
    {
      for (size_t i = 0; i < size; ++i)
      {
        push_front(value);
      }
    }
    ForwardList(const ForwardList<T> & other):
      head_(other.head_),
      size_(other.size_)
    {}
    ForwardList(ForwardList<T> && other)
    {
      swap(other);
    }
    ~ForwardList()
    {
      while (head_)
      {
        node_t * temp = head_->next_;
        delete head_;
        head_ = temp;
      }
    }
    ForwardList<T> & operator=(const ForwardList<T> & other)
    {
      ForwardList(other).swap(*this);
      return *this;
    }
    ForwardList<T> & operator=(ForwardList<T> && other)
    {
      swap(other);
      return *this;
    }
    size_t size() const
    {
      return size_;
    }
    ForwardIterator<T> begin()
    {
      return ForwardIterator<T>(head_);
    }
    ForwardIterator<T> end()
    {
      return ForwardIterator<T>();
    }
    void swap(ForwardList<T> & other)
    {
      std::swap(head_, other.head_);
      std::swap(size_, other.size_);
    }
    bool empty() const
    {
      return head_ == nullptr;
    }
    T & front()
    {
      return head_->data_;
    }
    void push_front(const T & value)
    {
      node_t * newHead = new node_t(value);
      newHead->next_ = head_;
      head_ = newHead;
      ++size_;
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::runtime_error("ForwardList is empty");
      }
      node_t * temp = head_;
      head_ = head_->next_;
      delete temp;
      --size_;
    }
    //void print()
    //{
    //  node_t * temp = head_;
    //  while (temp)
    //  {
    //    std::cout << temp->data_ << " ";
    //    temp = temp->next_;
    //  }
    //  std::cout << "\n";
    //}
    void reverse()
    {
      if (!head_)
      {
        return;
      }
      node_t * newHead = head_;
      node_t * tail = head_->next_;
      newHead->next_ = nullptr;
      while (tail)
      {
        node_t * temp = tail->next_;
        tail->next_ = newHead;
        newHead = tail;
        tail = temp;
      }
      head_ = newHead;
    }
  private:
    node_t * head_;
    size_t size_;
  };
}

#endif
