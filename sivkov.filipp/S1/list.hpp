#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"
#include "constIterator.hpp"

namespace sivkov
{
  template < typename T >
  class List
  {
  public:
    ConstIterator<T> cIterator;
    List():
      size_(0),
      head_(nullptr)
    {}
    List(size_t count, const T& value) :
      size_(0),
      head_(nullptr)
    {
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }

    List(const List& other) :
      size_(0),
      head_(nullptr)
    {
      Node<T>* current = other.head_;
      while (current != nullptr)
      {
        push_back(current->data);
        current = current->next;
      }
    }

    List(List&& other) noexcept:
      size_(0),
      head_(other.head_)
    {
      other.head_ = nullptr;
    }

    ~List() { clear(); }
    void push_front(const T& data);
    void push_back(T data);
    void clear();
    bool empty() const {return head_ == nullptr;}
    void pop_front();
    void pop_back();
    void swap(List& other);
    void reverse();
    void remove(const T& value);
    void assign(size_t count, const T& value);
    size_t getSize();
    T& front() { return head_->data; }
    ConstIterator<T> cbegin() const { return ConstIterator<T>(head_); }
    ConstIterator<T> cend() const { return ConstIterator<T>(nullptr); }

    private:
      size_t size_;
      Node<T>* head_;
    };

  template< typename T >
  void List<T>::push_front(const T& data)
  {
    Node<T>* temp = new Node<T>(data);
    temp->next = head_;
    head_ = temp;
    ++size_;
  }

  template< typename T >
  void List<T>::push_back(T data)
  {
    Node<T>* newNode = new Node<T>(data);
    if (empty())
    {
      head_ = newNode;
    }
    else
    {
      Node<T>* head = head_;
      while (head->next)
      {
          head = head->next;
      }
      head->next = newNode;
    }
   ++size_;
  }

  template< typename T >
  void List<T>::clear()
  {
    while (!(empty()))
    {
      pop_front();
    }
    size_ = 0;
  }

  template< typename T >
  void List<T>::pop_front()
  {
    if (empty())
    {
      throw;
    }
    Node<T>* head = head_;
    head_ = head_->next;
    delete head;
    --size_;
  }

  template< typename T >
  void List<T>::pop_back()
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
      Node<T>* head = head_;
      while (head->next->next != nullptr)
      {
        head = head->next;
      }
      delete head->next;
      head->next = nullptr;
    }
    --size_;
  }

  template< typename T >
  void List<T>::swap(List& other)
  {
    std::swap(head_, other.head_);
  }

  template< typename T >
  void List<T>::reverse()
  {
    if (!head_)
    {
      return;
    }
    Node< T >* result = head_;
    Node< T >* temp = head_->next;
    result->next = nullptr;
    while (temp)
    {
      Node< T >* rofl = temp->next;
      temp->next = result;
      result = temp;
      temp = rofl;
    }
    head_ = result;
  }

  template< typename T >
  void List<T>::remove(const T& value)
  {
    Node<T>* current = head_;
    Node<T>* prev = nullptr;

    while (current != nullptr)
    {
      if (current->data == value)
      {
        if (prev == nullptr)
        {
          head_ = current->next;
        }
        else
        {
          prev->next = current->next;
        }
        delete current;
        --size_;
        current = (prev == nullptr) ? head_ : prev->next;
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template< typename T >
  void List<T>::assign(size_t count, const T& value)
  {
    clear();

    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

  template< typename T >
  size_t List<T>::getSize()
  {
    return size_;
  }
}
#endif
