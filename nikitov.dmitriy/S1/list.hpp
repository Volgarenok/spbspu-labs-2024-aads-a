#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include "node.hpp"
#include "iterator.hpp"

namespace nikitov
{
  template< typename T >
  class Node;

  template< typename T >
  class List
  {
    friend class Node< T >;
    typedef ListIterator< int > iterator;
    typedef ListIterator< const int > constIterator;
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    ~List()
    {
      while (tail_->prev_ != nullptr)
      {
        Node< T >* ptr = tail_->prev_;
        delete tail_;
        tail_ = ptr;
      }
      delete tail_;
    }

    iterator begin()
    {
      return iterator(head_);
    }
    constIterator cbegin() const
    {
      return constIterator(head_);
    }
    iterator end()
    {
      return iterator(tail_);
    }
    constIterator cend() const
    {
      return constIterator(tail_);
    }

    T& front()
    {
      return head_->value_;
    }
    T& back()
    {
      return tail_->value_;
    }

    size_t size() const
    {
      return size_;
    }
    bool empty() const
    {
      return !size_;
    }

    void push_front(const T& value)
    {
      Node< T >* ptr = new Node< T >(value);
      ptr->next_ = head_;
      if (head_ != nullptr)
      {
        head_->prev_ = ptr;
      }
      else
      {
        head_ = ptr;
        tail_ = ptr;
      }
      head_ = ptr;
      ++size_;
    }
    void pop_front()
    {
      Node< T >* ptr = head_->next_;
      if (ptr != nullptr)
      {
        ptr->prev_ = nullptr;
      }
      else
      {
        tail_ = nullptr;
      }
      delete head_;
      head_ = ptr;
      --size_;
    }

    void push_back(const T& value)
    {
      Node< T >* ptr = new Node< T >(value);
      ptr->prev_ = tail_;
      if (tail_ != nullptr)
      {
        tail_->next_ = ptr;
      }
      else
      {
        head_ = ptr;
        tail_ = ptr;
      }
      tail_ = ptr;
      ++size_;
    }
    void pop_back()
    {
      Node< T >* ptr = tail_->prev_;
      if (ptr != nullptr)
      {
        ptr->next_ = nullptr;
      }
      else
      {
        head_ = nullptr;
      }
      delete tail_;
      tail_ = ptr;
      --size_;
    }

    void clear()
    {
      while (tail_->prev_ != nullptr)
      {
        Node< T >* ptr = tail_->prev_;
        delete tail_;
        tail_ = ptr;
      }
      delete tail_;
      size_ = 0;
    }
    void swap(List< T >& other)
    {
      std::swap(head_, other.head_);
      std::swap(tail_, other.tail_);
      std::swap(size_, other.size_);
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
