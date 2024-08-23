#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include "iterators.hpp"
#include "constIterators.hpp"
#include "node.hpp"
#include <stdexcept>
#include <cstddef>
#include <iostream>

namespace chernov
{
  template < typename T >
  class Iterators;

  template < typename T >
  class ConstIterators;

  template < typename T >
  class List
  {
  public:
    List():
      head_(nullptr),
      size_(0)
    {}

    List(const List< T >& obj):
      List()
    {
      if (!obj.isEmpty())
      {
        for (ConstIterators< T > it = obj.cbegin(); it != obj.cend(); ++it)
        {
          push_back(*it);
        }
      }
    }

    List(List< T >&& obj):
      head_(obj.head_),
      size_(obj.size_)
    {
      obj.head_ = nullptr;
      obj.size_ = 0;
    }

    List< T >& operator=(const List< T >& obj)
    {
      if (this == &obj)
      {
        return *this;
      }
      List< T > tmp(obj);
      std::swap(tmp, *this);
      return *this;
    }

    List< T >& operator=(List< T >&& obj)
    {
      if (this != &obj)
      {
        std::swap(head_, obj.head_);
        std::swap(size_, obj.size_);
      }
      return *this;
    }

    bool isEmpty() const
    {
      return size_ == 0;
    }

    size_t getSize() const
    {
      return size_;
    }

    const T& front() const
    {
      return head_->data_;
    }

    T& front()
    {
      return head_->data_;
    }

    const T& back() const
    {
      Node< T >* curr = head_;
      while (curr->next_)
      {
        curr = curr->next_;
      }
      return curr->data_;
    }

    T& back()
    {
      Node< T >* curr = head_;
      while (curr->next_)
      {
        curr = curr->next_;
      }
      return curr->data_;
    }

    void push_back(const T& value)
    {
      if (isEmpty())
      {
        push_front(value);
      }
      else
      {
        Node< T >* newNode = new Node< T >(value);
        Node< T >* curr = head_;
        while (curr->next_)
        {
          curr = curr->next_;
        }
        curr->next_ = newNode;
        ++size_;
      }
    }

    void push_front(const T& value)
    {
      if (isEmpty())
      {
        head_ = new Node< T >(value);
      }
      else
      {
        Node< T >* newNode = new Node< T >(value);
        newNode->next_ = head_;
        head_ = newNode;
      }
      ++size_;
    }

    void pop_front()
    {
      if (isEmpty())
      {
        return;
      }
      else if (head_->next_ == nullptr)
      {
        clear();
      }
      else
      {
        Node< T >* temp = head_;
        head_ = head_->next_;
        delete temp;
        --size_;
      }
    }

    void pop_back()
    {
      if (isEmpty())
      {
        return;
      }
      Node< T >* prev = head_;
      while (prev->next_ && prev->next_->next_)
      {
        prev = prev->next_;
      }
      delete prev->next_;
      prev->next_ = nullptr;
      --size_;
    }

    void clear()
    {
      Node< T >* current = head_;
      while (current != nullptr)
      {
        Node< T >* next = current->next_;
        delete current;
        current = next;
      }
      head_ = nullptr;
      size_ = 0;
    }

    void reverse()
    {
      Node< T >* prev = nullptr;
      Node< T >* current = head_;
      Node< T >* tempNext = nullptr;

      while (current != nullptr)
      {
        tempNext = current->next_;
        current->next_ = prev;
        prev = current;
        current = tempNext;
      }
      head_ = prev;
    }

    void swap(const Node< T >& other)
    {
      if ((isEmpty()))
      {
        throw std::invalid_argument("Not enough variables\n");
      }
      else
      {
        Node< T >* temporary = other->head_;
        other->head_ = head_;
        head_ = temporary;
      }
    }

    void fill(const T& value, size_t count)
    {
      for (size_t i = 0; i < count; i++)
      {
        push_back(value);
      }
    }

    void remove(const T& value)
    {
      remove_if([&](const T& number) -> bool { return value == number; });
    }

    template < class UnPredicate >
    void remove_if(UnPredicate p)
    {
      Node< T >* current = head_;
      Node< T >* previous = nullptr;

      while (current != nullptr)
      {
        if (p(current->data_))
        {
          if (previous == nullptr)
          {
            head_ = current->next_;
            delete current;
            current = head_;
          }
          else
          {
            previous->next_ = current->next_;
            delete current;
            current = previous->next_;
          }
          size_--;
        }
        else
        {
          previous = current;
          current = current->next_;
        }
      }
    }

    Iterators< T > begin()
    {
      return Iterators< T >(head_);
    }

    Iterators< T > end()
    {
      return Iterators< T >();
    }

    ConstIterators< T > cbegin() const
    {
      return ConstIterators< T >(head_);
    }

    ConstIterators< T > cend() const
    {
      return ConstIterators< T >();
    }

    ~List()
    {
      clear();
    }

  private:
    Node< T >* head_;
    size_t size_;
  };
}

#endif
