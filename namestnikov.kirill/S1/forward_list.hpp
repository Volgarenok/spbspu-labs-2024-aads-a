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
  public:
    using node_t = Node<T>;
    ForwardList():
      head_(nullptr),
      size_(0)
    {}
    ForwardList(size_t size, const T & value):
      head_(nullptr),
      size_(size)
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
        auto todel = head_;
        head_ = head_->next_;
        delete todel;
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
      return (!size_ && !head_);
    }
    T & front()
    {
      return head_->data_;
    }
    void push_front(const T & value)
    {
      Node<T> * newHead = new Node<T>(value);
      newHead->next_ = head_;
      head_ = newHead;
      ++size_;
    }
    void pop_front()
    {
      if (size_ == 0)
      {
        throw std::runtime_error("ForwardList is empty");
      }
      Node<T> * temp = head_->next_;
      delete head_;
      head_ = temp;
      --size_;
    }
    void print()
    {
      Node<T> * temp_ = head_;
      while (temp_)
      {
        std::cout << temp_->data_ << " ";
        temp_ = temp_->next_;
      }
      std::cout << "\n";
    }
    void reverse()
    {
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
    Node<T> * head_;
    size_t size_;
  };
}

#endif
