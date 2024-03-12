#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include "node.hpp"
#include <cstddef>
#include <iostream>

template < typename T >
class List
{
public:
  List() : head_(nullptr), tail_(nullptr), size_(0)
  {}

  bool isEmpty() const
  {
    return size_ == 0;
  }

  size_t getSize() const
  {
    return size_;
  }

  void push(const T& value)
  {
    if (isEmpty())
    {
      head_ = tail_ = new Node< T >{ nullptr, value };
      ++size_;
    }
    else
    {
      tail_->next_ = new Node< T >{ nullptr, value };
      tail_ = tail_->next_;
      ++size_;
    }
  }

  void pop()
  {
    if (isEmpty())
    {
      throw std::invalid_argument("Empty list\n");
    }
    else if (head_ == tail_)
    {
      delete tail_;
      head_ = tail_ = nullptr;
      --size_;
    }
    Node< T >* temp_ = head_->next;
    delete head_;
    head_ = temp_;
    --size_;
  }

  void print() const
  {
    Node< T >* current = head_;
    while (current != nullptr)
    {
      std::cout << current->data_ << " ";
      current = current->next_;
    }
  }

  void clear()
  {
    while (head_)
    {
      Node< T >* nextNode = head_->next_;
      delete head_;
      head_ = nextNode;
    }
    tail_ = nullptr;
    size_ = 0;
  }
private:

  Node< T >* head_;
  Node< T >* tail_;
  size_t size_;
};

#endif
