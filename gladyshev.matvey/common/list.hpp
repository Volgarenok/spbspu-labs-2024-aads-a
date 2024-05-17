#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>

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
      for (size_t i = 0; i < size; ++i)
      {
        push_front(data);
      }
    }
    List(const List& other):
      List()
    {
      detail::Node< T >* curr = other.head_;
      while (curr)
      {
        push_front(curr->data);
        curr = curr->next;
      }
      reverse();
    }
    List(List&& other) noexcept:
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    void clear() noexcept
    {
      while (!(empty()))
      {
        pop_front();
      }
    }
    bool empty() const noexcept
    {
      return head_ == nullptr;
    }
    void assign(size_t size, const T& value)
    {
      List< T > temp;
      for (size_t i = 0; i < size; ++i)
      {
        temp.push_front(value);
      }
      temp.reverse();
      swap(temp);
    }
    void reverse() noexcept
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
      auto checkPred =
        [&value](const T& data_)
        {
          return value == data_;
        };
      remove_if(checkPred);
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
    const T& front() const
    {
      return head_->data;
    }
    T& back()
    {
      detail::Node< T >* temp = head_;
      while (temp->next)
      {
        temp = temp->next;
      }
      return temp->data;
    }
    const T& back() const
    {
      detail::Node< T >* temp = head_;
      while (temp->next)
      {
        temp = temp->next;
      }
      return temp->data;
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::logic_error("empty list");
      }
      detail::Node< T >* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    void pop_back()
    {
      if (empty())
      {
        throw std::logic_error("empty list");
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
    constIterator cbegin() const noexcept
    {
      return constIterator(head_);
    }
    constIterator cend() const noexcept
    {
      return constIterator(nullptr);
    }
    iterator begin() noexcept
    {
      return iterator(head_);
    }
    iterator end() noexcept
    {
      return iterator(nullptr);
    }
  private:
    detail::Node< T >* head_;
  };
}

#endif
