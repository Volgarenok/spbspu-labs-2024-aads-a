#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

#include "node.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"

namespace gladyshev
{
  template < typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using constIterator = ConstIterator< T >;
    List():
      head_(nullptr)
    {}
    ~List()
    {
      clear();
    }
    List(const T& data, size_t size):
      List()
    {
      try
      {
        for (size_t i = 0; i < size; ++i)
        {
          push_front(data);
        }
      }
      catch (...)
      {
        clear();
      }
    }
    List(const List& other):
      head_(nullptr)
    {
      detail::Node< T > * curr = other.head_;
      while (curr != nullptr)
      {
        push_back(curr->data);
        curr = curr->next;
      }
    }
    List(List&& other):
      head_(other.head_)
    {
      other.head_ = nullptr;
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
    void assign(size_t size, const T& value)
    {
      clear();
      for (size_t i = 0; i < size; ++i)
      {
        push_front(value);
      }
    }
    void reverse()
    {
      detail::Node< T >* prev = nullptr;
      detail::Node< T >* current = head_;
      detail::Node< T >* temp = nullptr;
      while (current)
      {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
      }
      head_ = prev;
    }
    void remove(const T& value)
    {
      if (empty())
      {
        return;
      }
      if (head_->data = value)
      {
        pop_front();
        return;
      }
      detail::Node< T >* firstTemp = head_;
      detail::Node< T >* secondTemp = head_->next;
      while (secondTemp && secondTemp->data != value)
      {
        firstTemp = firstTemp->next;
        secondTemp = secondTemp->next;
      }
      if (!secondTemp)
      {
        return;
      }
      firstTemp->next = secondTemp->next;
      delete secondTemp;
    }
    template < typename UnaryPredicate >
    void remove_if(UnaryPredicate p)
    {
      detail::Node< T >* curr = head_;
      detail::Node< T >* temp = nullptr;
      while (curr)
      {
        if (p(curr->data))
        {
          if (curr == head_)
          {
            pop_front();
            curr = head_;
          }
          else
          {
            temp->next = curr->next;
            delete curr;
            curr = temp->next;
          }
        }
        else
        {
          temp = curr;
          curr = curr->next;
        }
      }
    }
    void push_back(const T& data)
    {
      detail::Node< T >* newNode = new detail::Node< T >(data);
      if (empty())
      {
        head_ = newNode;
      }
      else
      {
        detail::Node< T >* temp = head_;
        while (temp->next)
        {
          temp = temp->next;
        }
        temp->next = newNode;
      }
    }
    void push_front(const T& data)
    {
      detail::Node< T >* temp = new detail::Node< T >(data);
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
        return;
      }
      detail::Node< T >* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    void pop_back()
    {
      if (empty())
      {
        return;
      }
      if (!head_->next)
      {
        delete head_;
        head_ = nullptr;
      }
      else
      {
        detail::Node< T >* temp = head_;
        while (temp->next->next)
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
    constIterator cbegin() const
    {
      return constIterator(head_);
    }
    constIterator cend() const
    {
      return constIterator(nullptr);
    }
    iterator begin()
    {
      return iterator(head_);
    }
    iterator end()
    {
      return iterator(nullptr);
    }
  private:
    detail::Node< T >* head_;
  };
}

#endif
