#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
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
    ForwardList(ForwardList<T> && other)
    {
      swap(other);
    }
    ~ForwardList()
    {
      clearForwardList();
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
      newHead->next = head_;
      head_ = newHead;
      ++size_;
    }
    void pop_front()
    {
      if (size_ == 0)
      {
        throw std::runtime_error("ForwardList is empty");
      }
      Node<T> * temp = head_;
      head_ = head_->next;
      delete temp;
    }
  private:
    Node<T> * head_;
    size_t size_;
  };
}

#endif
