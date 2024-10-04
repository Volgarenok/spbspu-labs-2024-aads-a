#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <iostream>
#include <cstddef>
#include "iterator.hpp"
#include "constiterator.hpp"
#include "node.hpp"

namespace vojuck
{
  template< typename T >
  class List
  {
    friend struct IteratorList< T >;
    friend struct ConstIteratorList< T >;
  public:
    using iterator = IteratorList< T >;
    using const_iterator = ConstIteratorList< T >;

    List():
      head_(nullptr),
      size_(0)
    {}
    List(const List< T > & other):
      List()
    {
      details::Node< T >* current = other.head_;
      while (current)
      {
        push_back(current->data_);
        current = current->next_;
      }
      size_ = other.size_;
    }
    List(List && other) noexcept :
      head_(other.head_),
      size_(other.size_)
    {
      other.head_ = nullptr;
      other.size_ = 0;
    }
    ~List()
    {
      clear();
    }

    List & operator=(const List< T > & other)
    {
      if( this != &other)
      {
        clear();
        details::Node< T >* current = other.head_;
        while (current)
        {
          push_back(current->data);
          current = current->next;
        }
        size_ = other.size_;
      }
      return *this;
    }
    List & operator=(List && other) noexcept
    {
      if (this != &other)
      {
        clear();
        head_ = other.head_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }


    T & front()
    {
      return head_->data_;
    }

    iterator begin() noexcept
    {
      return iterator(head_);
    }
    iterator end() noexcept
    {
      return iterator(nullptr);
    }
    const_iterator cbegin() const noexcept
    {
      return const_iterator(head_);
    }
    const_iterator cend() const noexcept
    {
      return const_iterator(nullptr);
    }

    bool empty() const noexcept
    {
      return head_ == nullptr;
    }

    void pop_front()
    {
      if (empty())
      {
        throw std::logic_error("empty list");
      }
      details::Node< T > *temp = head_;
      head_ = head_->next_;
      delete temp;
      size_--;
    }
    void clear() noexcept
    {
      while(!empty())
      {
        pop_front();
      }
    }

    void push_front(const T & data_)
    {
      details::Node< T > *temp = new details::Node< T >(data_);
      temp->next_ = head_;
      head_ = temp;
      size_++;
    }
    void swap(List< T > & other) noexcept
    {
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
    }
    void push_back(const T& data)
    {
      details::Node<T> *newNode = new details::Node<T>(data);
      if (head_ == nullptr)
      {
        head_ = newNode;
      }
      else
      {
        details::Node<T> *current = head_;
        while (current->next_ != nullptr)
        {
          current = current->next_;
        }
        current->next_ = newNode;
      }
      size_++;
    }

    void reverse() noexcept
    {
      details::Node<T> *prev = nullptr;
      details::Node<T> *current = head_;
      while (current != nullptr)
      {
        details::Node<T> *next = current->next_;
        current->next_ = prev;
        prev = current;
        current = next;
      }
      head_ = prev;
    }
  private:
    size_t size_;
    details::Node< T > *head_;
  };
}

#endif
