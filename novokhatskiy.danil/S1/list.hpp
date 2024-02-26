#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "iterator.hpp"
#include "node.hpp"

namespace novokhatskiy
{
  template <typename T >
  class Iterator;

  template <typename T >
  class Node;

  template <typename T >
  class List
  {
    friend class novokhatskiy::Iterator<T>;
  public:
    using iterPtr = Iterator<T>*;
    List():
      head_(nullptr)
    {}
    List(List<T>* other):
      head_(other->head_)
    {}
    List(List&& other) noexcept :
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    iterPtr begin() //const
    {
      if (head_ != nullptr)
      {
        iterator_.node_ = head_;
        return iterator_;
      }
    }
    iterPtr end()
    {
      iterPtr temp = iterator_;
      temp->node_ = head_;
      while (temp->node_ != nullptr && temp.node_->next_ != nullptr)
      {
        temp = temp.node_->next_;
      }
      return temp;
    }
        
    bool empty() const
    {
      return (head_ == nullptr);
    }
    const T& front() const
    {
      return head_->value_;
    }
    void push_front(const T& value)
    {
      Node<T>* ptr = new Node<T>(value);
      ptr->next_ = head_;
      head_ = ptr;
    }
    void pop_front()
    {
      if (empty()) 
      {
        std::cerr << "The forward_list is empty\n";
        return;
      }
      Node<T>* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    void clear()
    {
      while (!empty())
      {
        pop_front();
      }
    }
    void swap(List<T>& other)
    {
      std::swap(head_, other.head_);
    }
    void remove(const T& value)
    {
      Node<T>* current = head_;
      Node<T>* prev = nullptr;
      while (current != nullptr)
      {
        if (current->value_ == value)
        {
          head_ = current->next_;
          delete current;
          current = head_;
        }
        else 
        {
          prev->next_ = current->next_;
          delete current;
          current = prev->next_;
        }
      }
    }
    void print() {
      //Node<T>* current = head_;
      while (head_ != nullptr) {
        std::cout << head_->value_ << " ";
        head_ = head_->next_;
      }
      std::cout << std::endl;
    }
    ~List()
    {
     /*while (head_->next_ != nullptr)
      {
        Node<T>* ptr = head_->next_;
        delete head_;
        head_ = ptr;
      }
     */ 
      clear();
    }
  private:
    Node<T>* head_;
    Iterator<T>* iterator_;
  };
}

#endif 
