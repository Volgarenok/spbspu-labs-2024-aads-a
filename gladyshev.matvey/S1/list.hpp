#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

#include "node.hpp"
#include "iterator.hpp"

namespace gladyshev
{
  template <typename T>
  class List
  {
  public:
    typedef Iterator<T> iterator;
    List():
      head_(nullptr)
    {}
    ~List()
    {
      clear();
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
      Node<T>* prev = nullptr;
      Node<T>* current = head_;
      Node<T>* temp = nullptr;
      while (current != nullptr)
      {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
      }
      head_ = prev;
    }
    void push_back(T data)
    {
      Node<T>* newNode = new Node<T>(data);
      if (empty())
      {
        head_ = newNode;
      }
      else
      {
        Node<T>* temp = head_;
        while (temp->next)
        {
          temp = temp->next;
        }
        temp->next = newNode;
      }
    }
    void push_front(const T& data)
    {
      Node<T>* temp = new Node<T>(data);
      temp->next = head_;
      head_ = temp;
    }
    T& front()
    {
      return head_->data;
    }
    void pop_front()
    {
      if (empty())
      {
        throw;
      }
      Node<T>* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    void pop_back()
    {
      if (empty())
      {
        throw;
      }
      if (head_->next == nullptr)
      {
        delete head_;
        head_ = nullptr;
      }
      else
      {
        Node<T>* temp = head_;
        while (temp->next->next != nullptr)
        {
          temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
      }
    }
    void swap(List& other)
    {
      std::swap(head_, other.head_);
    }
    iterator begin() const
    {
      return iterator(head_);
    }
    iterator end() const
    {
      return iterator(nullptr);
    }
  private:
    Node<T>* head_;
  };
}

#endif
