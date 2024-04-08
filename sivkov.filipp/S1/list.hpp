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
      size(0),
      head_(nullptr)
    {}
    List(std::size_t count, const T& value) :
      size(0),
      head_(nullptr)
    {
      for (std::size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }

    List(const List& other) :
      size(0),
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
      size(0),
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
    void assign(std::size_t count, const T& value);
    size_t getSize();
    T& front() { return head_->data; }
    ConstIterator<T> cbegin() const { return ConstIterator<T>(head_); }
    ConstIterator<T> cend() const { return ConstIterator<T>(nullptr); }
    T& operator[](const int index);

    private:
      size_t size;
      Node<T>* head_;
    };

  template< typename T >
  void List<T>::push_front(const T& data)
  {
    Node<T>* temp = new Node<T>(data);
    temp->next = head_;
    head_ = temp;
    ++size;
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
   ++size;
  }

  template< typename T >
  void List<T>::clear()
  {
    while (!(empty()))
    {
      pop_front();
    }
    size = 0;
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
    --size;
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
    --size;
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
        --size;
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

    for (std::size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

  template< typename T >
  size_t List<T>::getSize()
  {
    return size;
  }

  template< typename T >
  T& List<T>::operator[](const int index)
  {
    int counter = 0;
    Node<T>* current = this->head;
    if (size <= index || index < 0)
    {
      throw std::out_of_range("Index out of range");
    }
    while (current != nullptr)
    {
      if (counter == index)
      {
        return current->data;
      }
      current = current->pNext;
      counter++;
    }
    throw std::logic_error("Index not found");
  }
}
#endif
