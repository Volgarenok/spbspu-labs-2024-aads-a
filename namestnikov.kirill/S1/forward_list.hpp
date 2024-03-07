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
    using node_t = Node<T>;
  public:
    ForwardList() :
      head_(nullptr)
    {}
    ForwardList(size_t count, const T & value) :
      head_(nullptr)
    {
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_front(value);
        }
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw std::invalid_argument("Too many args for a list");
      }
    }
    ForwardList(const ForwardList<T> & other) :
      head_(nullptr)
    {
      node_t * temp = other.head_;
      while (temp)
      {
        push_front(temp->data_);
        temp = temp->next_;
      }
    }
    ForwardList<T> & operator=(const ForwardList<T> & other)
    {
      ForwardList<T> temp(other);
      if (std::addressof(other) != this)
      {
        swap(temp);
      }
      return *this;
    }
    ForwardList(ForwardList<T> && other)
    {
      swap(other);
    }
    ForwardList<T> & operator=(ForwardList<T> && other)
    {
      ForwardList<T> temp(std::move(other));
      if (std::addressof(other) != this)
      {
        swap(temp);
      }
      return *this;
    }
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
    }
    void push_front(const T & data)
    {
      node_t * newHead = new node_t(data);
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
    size_t size()
    {
      size_t size = 0;
      node_t * temp = head_;
      while (head_)
      {
        ++size;
        head_ = head_->next_;
      }
      head_ = temp;
      return size;
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::runtime_error("ForwardList is empty");
      }
      node_t * oldHead = head_;
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
    void print()
    {
      node_t * temp = head_;
      while (temp)
      {
        std::cout << temp->data_ << " ";
        temp = temp ->next_;
      }
      std::cout << "\n";
    }
  private:
    node_t * head_;
  };
}

#endif
