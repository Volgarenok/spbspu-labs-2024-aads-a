#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
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

    void push_front(T value)
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
    void push_back(T value)
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
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
