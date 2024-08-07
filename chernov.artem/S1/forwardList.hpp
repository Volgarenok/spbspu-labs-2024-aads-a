#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include "iterators.hpp"
#include "constIterators.hpp"
#include "node.hpp"
#include <cstddef>
#include <iostream>

namespace chernov
{
  template < typename T >
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    ~List()
    {
      clear();
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

    List(const List< T >& obj)
    {
      head_ = obj.head_;
      tail_ = obj.tail_;
      size_ = obj.size_;
    }

    List(List< T >&& obj)
    {
      head_ = obj.head_;
      tail_ = obj.tail_;
      size_ = obj.size_;
      obj.clear();
    }

    List< T >& operator=(const List< T >& obj)
    {
      List< T > tmp(obj);
      std::swap(tmp, *this);
      return *this;
    }

    List< T >& operator=(List< T >&& obj)
    {
      List< T > tmp(obj);
      std::swap(tmp, *this);
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

    const T& front()
    {
      return head_->data_;
    }

    void push_back(const T& value)
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

    void push_front(const T& value)
    {
      if (isEmpty())
      {
        head_ = tail_ = new Node< T >{ nullptr, value };
        ++size_;
      }
      else
      {
        Node< T >* newNode = new Node< T >(value);
        newNode->next_ = head_;
        head_ = newNode;
        ++size_;
      }
    }

    void pop_front()
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
      Node< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
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
      if ((isEmpty()))
      {
        return;
      }
      Node<T>* current = head_;
      while (current != nullptr)
      {
        Node<T>* nextNode = current->next_;
        delete current;
        current = nextNode;
      }
      head_ = tail_ = nullptr;
      size_ = 0;
    }

    void swap(const Node< T >& other)
    {
      if ((isEmpty()))
      {
        throw std::invalid_argument("Not enough variables\n");
      }
      else
      {
        Node<T>* temporary = other->head_;
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
      Node<T>* current = head_;
      Node<T>* previous = nullptr;

      while (current != nullptr)
      {
        if (p(current->data_))
        {
          if (previous == nullptr)
          {
            head_ = current->next_;
            if (tail_ == current)
            {
              tail_ = nullptr;
            }
            delete current;
            current = head_;
          }
          else
          {
            previous->next_ = current->next_;
            if (tail_ == current)
            {
              tail_ = previous;
            }
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

  private:

    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}

#endif
