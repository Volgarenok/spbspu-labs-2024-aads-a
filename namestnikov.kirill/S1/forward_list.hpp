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
  template<class T>
  class ForwardList
  {
    using iterator_t = ForwardIterator<T>;
  public:
    ForwardList() :
      head_(nullptr)
    {}
    void clear()
    {
      while (!(empty()))
      {
        pop_front();
      }
    }
    bool empty() const
    {
      return head_ == nullptr;
    }
    void reverse()
    {
      if (head_)
      {
        Node<T> * newHead = head_;
        Node<T> * tail = head_->next_;
        newHead->next_ = nullptr;
        while (tail)
        {
          Node<T> * temp = tail->next_;
          tail->next_ = newHead;
          newHead = tail;
          tail = temp;
        }
        head_ = newHead;
      }
    }
    void push_front(const T & data)
    {
      Node<T> * newHead = new Node<T>(data);
      newHead->next_ = head_;
      head_ = newHead;
    }
    T & front()
    {
      return head_->data_;
    }
    void swap(ForwardList & other)
    {
      std::swap(head_, other.head_);
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::runtime_error("ForwardList is empty");
      }
      Node<T> * oldHead = head_;
      head_ = head_->next_;
      delete oldHead;
    }
    iterator_t begin() const
    {
      return iterator_t(head_);
    }
    iterator_t end() const
    {
      return iterator_t(nullptr);
    }
    ~ForwardList()
    {
      clear();
    }
  private:
    Node<T> * head_;
  };
}

#endif
