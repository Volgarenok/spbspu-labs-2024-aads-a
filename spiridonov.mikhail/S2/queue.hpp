#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include "node.hpp"

namespace spiridonov
{
  template < typename T >
  class Queue
  {
  public:
    Queue(): head_(nullptr), tail_(nullptr), size_(0)
    {}

    Queue(const Queue< T >& obj): Queue()
    {
      const Node< T >* temp = obj.head_;

      while (temp)
      {
        push(temp->data_);
        temp = temp->next_;
      }
    }

    Queue(Queue< T >&& obj): head_(obj.head_), tail_(obj.tail_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }

    ~Queue()
    {
      clear();
    }

    void push(const T& value)
    {
      if (isEmpty())
      {
        head_ = tail_ = new Node< T >{ value, nullptr };
      }
      else
      {
        tail_->next_ = new Node< T >{ value, nullptr };
        tail_ = tail_->next_;
      }

      ++size_;
    }

    const T& getTop() const
    {
      if (isEmpty())
      {
        throw std::out_of_range("Queue is empty");
      }

      return head_->data_;
    }

    T& getTop()
    {
      if (isEmpty())
      {
        throw std::out_of_range("Queue is empty");
      }

      return head_->data_;
    }

    size_t getSize()
    {
      return size_;
    }

    void pop()
    {
      if (isEmpty())
      {
        throw std::underflow_error("Queue is empty");
      }
      else if (tail_ == head_)
      {
        delete tail_;
        tail_ = head_ = nullptr;
      }
      else
      {
        Node< T >* temp = head_->next_;
        delete head_;
        head_ = temp;
      }

      --size_;
    }

    bool isEmpty() const
    {
      return head_ == nullptr;
    }

    void clear()
    {
      while (head_)
      {
        Node< T >* temp = head_->next_;
        delete head_;
        head_ = temp;
      }

      head_ = nullptr;
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
