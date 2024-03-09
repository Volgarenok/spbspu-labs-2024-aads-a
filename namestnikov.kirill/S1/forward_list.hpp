#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "node.hpp"
#include "iterators.hpp"
#include "const_iterators.hpp"

namespace namestnikov
{
  template<class T>
  class ForwardList
  {
    using iterator_t = ForwardIterator<T>;
    using const_it_t = ConstForwardIterator<T>;
    using node_t = Node<T>;
  public:
    ForwardList() :
      head_(nullptr)
    {}
    ForwardList(size_t count, const T & value) :
      head_(nullptr)
    {
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_front(value);
        }
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw std::invalid_argument("Too many args for a list");
      }
    }
    ForwardList(const ForwardList<T> & other) :
      head_(nullptr)
    {
      node_t * temp = other.head_;
      try
      {
        while (temp)
        {
          push_front(temp->data_);
          temp = temp->next_;
        }
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw std::invalid_argument("Too many args for a list");
      }
    }
    ForwardList(std::initializer_list<T> list) :
      head_(nullptr)
    {
      auto begin = list.begin();
      auto end = list.end();
      while (begin != end)
      {
        try
        {
          push_front(*begin);
          ++begin;
        }
        catch (const std::bad_alloc &)
        {
          clear();
          throw std::invalid_argument("Too many args for a list");
        }
      }
      reverse();
    }
    ForwardList<T> & operator=(const ForwardList<T> & other)
    {
      ForwardList<T> temp(other);
      if (std::addressof(other) != this)
      {
        swap(temp);
      }
      return *this;
    }
    ForwardList(ForwardList<T> && other) :
      head_(other.head_)
    {
      other.head_ = nullptr;
    }
    ForwardList<T> & operator=(ForwardList<T> && other)
    {
      ForwardList<T> temp(std::move(other));
      if (std::addressof(other) != this)
      {
        swap(temp);
      }
      return *this;
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
      if (head_)
      {
        node_t * newHead = head_;
        node_t * tail = head_->next_;
        newHead->next_ = nullptr;
        while (tail)
        {
          node_t * temp = tail->next_;
          tail->next_ = newHead;
          newHead = tail;
          tail = temp;
        }
        head_ = newHead;
      }
    }
    void push_front(const T & data)
    {
      node_t * newHead = new node_t(data);
      newHead->next_ = head_;
      head_ = newHead;
    }
    T & front()
    {
      return head_->data_;
    }
    void swap(ForwardList & other)
    {
      std::swap(head_, other.head_);
    }
    size_t max_size()
    {
      size_t size = 0;
      node_t * temp = head_;
      while (head_)
      {
        ++size;
        head_ = head_->next_;
      }
      head_ = temp;
      return size;
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::runtime_error("ForwardList is empty");
      }
      node_t * oldHead = head_;
      head_ = head_->next_;
      delete oldHead;
    }
    void remove(const T & value)
    {
      node_t * prev = nullptr;
      node_t * temp = head_;
      while (temp)
      {
        if (temp->data_ == value)
        {
          node_t * todel = temp;
          if (prev)
          {
            prev->next_ = temp->next_;
          }
          else
          {
            head_ = temp->next_;
          }
          temp = temp->next_;
          delete todel;
        }
        else
        {
          prev = temp;
          temp = temp->next_;
        }
      }
    }
    template <class Predicate>
    void remove_if(Predicate p)
    {
      node_t * prev = nullptr;
      node_t * temp = head_;
      while (temp)
      {
        if (p(temp->data_))
        {
          node_t * todel = temp;
          if (prev)
          {
            prev->next_ = temp->next_;
          }
          else
          {
            head_ = temp->next_;
          }
          temp = temp->next_;
          delete todel;
        }
        else
        {
          prev = temp;
          temp = temp->next_;
        }
      }
    }
    void assign(size_t count, const T & value)
    {
      clear();
      try
      {
        for (size_t i = 0; i < count; ++i)
        {
          push_front(value);
        }
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw std::invalid_argument("Too many args for a list");
      }
    }
    void assign(std::initializer_list<T> list)
    {
      clear();
      try
      {
        auto begin = list.begin();
        auto end = list.end();
        while (begin != end)
        {
          push_front(*begin);
          ++begin;
        }
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw std::invalid_argument("Too many args for a list");
      }
      reverse();
    }
    void assign(iterator_t begin, iterator_t end)
    {
      clear();
      try
      {
        while (begin != end)
        {
          push_front(*begin);
          ++begin;
        }
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw std::invalid_argument("Too many args for a list");
      }
      reverse();
    }
    T & operator[](const size_t index)
    {
      size_t counter = 0;
      auto temp = head_;
      while (temp)
      {
        if (counter == index)
        {
          break;
        }
        temp = temp->next_;
        ++counter;
      }
      return temp->data_;
    }
    bool operator==(ForwardList<T> & other)
    {
      size_t size = std::min(max_size(), other.max_size());
      node_t * ourNode = head_;
      node_t * otherNode = other.head_;
      for (size_t i = 0; i < size; ++i)
      {
        if (ourNode->data_ != otherNode->data_)
        {
          return false;
        }
        ourNode = ourNode->next_;
        otherNode = otherNode->next_;
      }
      return true;
    }
    bool operator<(ForwardList<T> & other)
    {
      size_t size = std::min(max_size(), other.max_size());
      node_t * ourNode = head_;
      node_t * otherNode = other.head_;
      for (size_t i = 0; i < size; ++i)
      {
        if (ourNode->data_ >= otherNode->data_)
        {
          return false;
        }
        ourNode = ourNode->next_;
        otherNode = otherNode->next_;
      }
      return true;
    }
    bool operator!=(ForwardList<T> & other)
    {
      return !(*this == other);
    }
    bool operator>(ForwardList<T> & other)
    {
      return !(*this <= other);
    }
    bool operator<=(ForwardList<T> & other)
    {
      return ((*this < other) || (*this == other));
    }
    bool operator>=(ForwardList<T> & other)
    {
      return ((*this > other) || (*this == other));
    }
    iterator_t begin() const
    {
      return iterator_t(head_);
    }
    const_it_t cbegin() const
    {
      return const_it_t(head_);
    }
    iterator_t end() const
    {
      return iterator_t(nullptr);
    }
    const_it_t cend() const
    {
      return const_it_t(nullptr);
    }
    ~ForwardList()
    {
      clear();
    }
    void print()
    {
      node_t * temp = head_;
      while (temp)
      {
        std::cout << temp->data_ << " ";
        temp = temp ->next_;
      }
      std::cout << "\n";
    }
  private:
    node_t * head_;
  };
}

#endif
