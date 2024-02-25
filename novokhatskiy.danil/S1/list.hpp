#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "iterator.hpp"

namespace novokhatskiy
{
  template <typename T >
  class Iterator;

  template <typename T >
  class List
  {
    friend class novokhatskiy::Iterator<T>;
  public:
    List():
      head_(nullptr)
    {}
    List(List&& other) noexcept :
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    novokhatskiy::Iterator<T>* begin() const
    {
      if (head_ != nullptr)
      {
        return head_;
      }
    }
    bool empty() const
    {
      return (head_ == nullptr);
    }
    const T& front() const
    {
      return head_->value_;
    }
    ~List()
    {
      while (head_->next_ != nullptr)
      {
        Node* ptr = head_->next_;
        delete head_;
        head_ = ptr;
      }
    }
    void push_front(const T& value)
    {
      Node* ptr = new Node(value);
      ptr->next_ = head_;
      head_ = ptr;
    }
    void pop_front()
    {
      if (head_ == nullptr) // можно было использовать метод empty()?
      {
        std::cerr << "The forward_list is empty\n";
        return;
      }
      Node* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  private:
    struct Node
    {
      T value_;
      Node* next_;
      Node(const T& value, Node* next = nullptr):
        value_(value),
        next_(next)
      {}
    };
    Node* head_;
  };
}

#endif 
