#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include "node.hpp"

namespace spiridonov
{
  template < typename T >

  class Stack
  {
  public:
    Stack(): head_(nullptr), size_(0)
    {}

    Stack(const Stack< T >& obj): head_(nullptr), size_(0)
    {
      Node< T >* temp = obj.head_;

      while (temp)
      {
        push(temp->data_);
        temp = temp->next_;
      }
    }

    Stack(Stack< T >&& obj): head_(obj.head_), size_(obj.size_)
    {
      obj.head_ = nullptr;
      obj.size_ = 0;
    }

    ~Stack()
    {
      clear();
    }

    void push(const T& value)
    {
      Node< T >* temp = new Node< T >;
      temp->data_ = value;
      temp->next_ = head_;
      head_ = temp;
      size_++;
    }

    const T& getTop() const
    {
      if (isEmpty())
      {
        throw std::out_of_range("Stack is empty");
      }

      return head_->data_;
    }

    void pop()
    {
      if (isEmpty())
      {
        throw std::out_of_range("Stack is empty");
      }

      Node< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
      size_--;
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
      size_ = 0;
    }

    size_t getSize() const
    {
      return size_;
    }

  private:
    Node< T >* head_;
    size_t size_;
  };
}
#endif
