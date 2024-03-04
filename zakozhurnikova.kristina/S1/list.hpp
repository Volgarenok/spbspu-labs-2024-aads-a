#ifndef LIST_HPP
#define LIST_HPP
#include <utility>
#include <iostream>
#include <cstddef>
#include <string>
#include "node.hpp"

namespace zakozhurnikova
{
  template <typename T>
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    List(const List& rhs) :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      Node< T >* temp = rhs.head_;
      while (temp)
      {
        push(temp->data);
        temp = temp->next;
      }
    }

    List(List&& rhs) noexcept :
      head_(rhs.head_),
      tail_(rhs.tail_),
      size_(size_)
    {
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
    }

    List& operator=(const List& rhs)
    {
      if (this != &rhs)
      {
        List temp(rhs);
        clear();
        head_ = temp.head_;
        tail_ = temp.tail_;
      }
      return *this;
    }

    List operator=(List&& rhs) noexcept
    {
      if (this != &rhs)
      {
        swap(rhs);
      }
      return this;
    }

    ~List()
    {
      clear();
    }

    void push(T data)
    {
      Node< T >* temp = new Node< T >{ data };

      if (!tail_)
      {
        tail_ = temp;
        head_ = temp;
      }
      else
      {
        tail_->next = temp;
        temp->prev = tail_;
        tail_ = temp;
      }
      ++size_;
    }

    void pop() noexcept
    {
      Node< T >* toDelete = tail_;
      tail_ = tail_->prev;
      if (!tail_)
      {
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        tail_->next = nullptr;
      }
      delete toDelete;
      --size_;
    }

    size_t size() const
    {
      return size_;
    }

    void clear() noexcept
    {
      while (tail_)
      {
        pop();
      }
      head_ = nullptr;
    }

    bool empty() noexcept
    {
      return size_ == 0;
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
