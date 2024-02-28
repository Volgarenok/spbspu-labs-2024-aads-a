#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include "node.hpp"
#include "listiterator.hpp"

namespace piyavkin
{
  template< class T >
  class List
  {
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    List(const T& value, size_t count):
      List()
    {
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }
    List(ListIterator< T > start, ListIterator< T > finish):
      List()
    {
      push_back(*start);
      while (start != finish)
      {
        ++start;
        push_back(*start);
      }
    }
    List(const List< T >& rhs):
      List()
    {
      try
      {
        Node< T >* node = rhs.head_;
        while (size_ != rhs.size_)
        {
          push_back(node->value_);
          node = node->next_;
        }
      }
      catch (const std::exception& e)
      {
        for (size_t j = 0; j < size_; ++j)
        {
          pop_front();
        }
        throw;
      }
    }
    List(const List< T >&& rhs)
    {
      swap(rhs);
    }
    bool operator<(List< T >& rhs)
    {
      size_t min_size = std::min(rhs.size_, size_);
      Node< T >* node = head_;
      Node< T >* rhs_node = rhs.head_;
      for (size_t i = 0; i < min_size; ++i)
      {
        if (node->value_ != rhs_node->value_)
        {
          return node->value_ < rhs_node->value_;
        }
        node = node->next_;
        rhs_node = rhs_node->next_;
      }
      return false;
    }
    bool operator>=(List< T >& rhs)
    {
      return !(*this < rhs);
    }
    bool operator<=(List< T >& rhs)
    {
      return !(rhs < *this);
    }
    bool operator>(List< T >& rhs)
    {
      return (rhs < *this);
    }
    bool operator==(List< T >& rhs)
    {
      return !(*this < rhs) && !(rhs < *this);
    }
    bool operator!=(List< T >& rhs)
    {
      return !(rhs == *this);
    }
    List< T >& operator=(const List< T >&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
      }
      return *this;
    }
    List< T >& operator=(const List< T >& rhs)
    {
      if (this != std::addressof(rhs))
      {
        List< T > temp(rhs);
        temp.swap(*this);
      }
      return *this;
    }
    ~List()
    {
      clear();
    }
    void assign(const T& value, size_t count)
    {
      clear();
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }
    void remove(const T& value)
    {
      Node< T >* node = head_;
      while (node->value_ != value)
      {
        node = node->next_;
      }
      if (node == head_)
      {
        pop_front();
      }
      else if (node == tail_)
      {
        pop_back();
      }
      else
      {
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        delete node;
        --size_;
      }
    }
    template< class Functor >
    void remove_if(Functor f)
    {
      Node< T >* node = head_;
      while (node)
      {
        if (f(node->value_))
        {
          if (node == head_)
          {
            pop_front();
            node = head_;
          }
          else if (node == tail_)
          {
            pop_back();
            node = nullptr;
          }
          else
          {
            Node< T >* temp = node;
            node->next_->prev_ = node->prev_;
            node->prev_->next_ = node->next_;
            node = node->next_;
            delete temp;
            --size_;
          }
        }
        else
        {
          node = node->next_;
        }
      }
    }
    void swap(List< T >& list)
    {
      std::swap(list.head_, head_);
      std::swap(list.tail_, tail_);
      std::swap(list.size_, size_);
    }
    const T& at(size_t i) const
    {
      if (i >= size_)
      {
        throw std::logic_error("Element outside the list");
      }
      return operator[](i);
    }
    T& at(size_t i)
    {
      return const_cast< T& >(static_cast< const List< T >& >(*this).at(i));
    }
    T& operator[](size_t i)
    {
      return const_cast< T& >(static_cast< const List< T >& >(*this).operator[](i));
    }
    const T& operator[](size_t i) const
    {
      ListIterator< T > iterator(head_);
      for (size_t j = 0; j < i; ++j)
      {
        ++iterator;
      }
      return *iterator;
    }
    size_t size() const
    {
      return size_;
    }
    T& back() const
    {
      return tail_->value_;
    }
    T& front() const
    {
      return head_->value_;
    }
    ListIterator< T > begin()
    {
      return ListIterator< T >(head_);
    }
    ListIterator< T > end()
    {
      return ListIterator< T >(tail_);
    }
    const ListIterator< T > cbegin() const
    {
      return ListIterator< T >(head_);
    }
    const ListIterator< T > cend() const
    {
      return ListIterator< T >(tail_);
    }
    void erase(const ListIterator< T >& it)
    {
      if (it == begin())
      {
        pop_front();
      }
      else if (it == end())
      {
        pop_back();
      }
      else
      {
        ListIterator< T > iterator(head_);
        Node< T >* node = head_;
        while (iterator != it)
        {
          node = node->next_;
          ++iterator;
        }
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        delete node;
        --size_;
      }
    }
    void erase(ListIterator< T >& it_start, const ListIterator< T >& it_finish)
    {
      while (it_start != it_finish)
      {
        erase(it_start++);
      }
      erase(it_start);
    }
    void insert(ListIterator< T >& it, const T& value)
    {
      if (it == begin())
      {
        push_front(value);
      }
      else if (++it == end())
      {
        push_back(value);
      }
      else
      {
        --it;
        ListIterator< T > iterator(head_);
        Node< T >* node = head_;
        while (iterator != it)
        {
          node = node->next_;
          ++iterator;
        }
        Node< T >* new_node = new Node< T >(value);
        new_node->next_ = node;
        new_node->prev_ = node->prev_;
        node->prev_ = new_node;
        new_node->prev_->next_ = new_node;
        ++size_;
      }
    }
    bool empty() const
    {
      return size_ == 0;
    }
    void push_front(const T& value)
    {
      Node< T >* new_node = new Node< T >(value);
      new_node->next_ = head_;
      if (head_)
      {
        head_->prev_ = new_node;
      }
      if (!tail_)
      {
        tail_ = new_node;
      }
      head_ = new_node;
      ++size_;
    }
    void push_back(const T& value)
    {
      Node< T >* new_node = new Node< T >(value);
      new_node->prev_ = tail_;
      if (tail_)
      {
        tail_->next_ = new_node;
      }
      if (!head_)
      {
        head_ = new_node;
      }
      tail_ = new_node;
      ++size_;
    }
    void pop_back()
    {
      if (empty())
      {
        throw std::logic_error("The list is empty");
      }
      else if (size_ == 1)
      {
        delete tail_;
        --size_;
      }
      else
      {
        tail_ = tail_->prev_;
        delete tail_->next_;
        --size_;
      }
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::logic_error("The list is empty");
      }
      else if (size_ == 1)
      {
        delete head_;
        --size_;
      }
      else
      {
        head_ = head_->next_;
        delete head_->prev_;
        --size_;
      }
    }
    void clear()
    {
      while (size() != 0)
      {
        pop_back();
      }
    }
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}

#endif
