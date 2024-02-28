#ifndef BDLIST_HPP
#define BDLIST_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace ishmuratov
{
  template< class T >
  class List
  {
    public:
      List():
        head_(nullptr),
        tail_(nullptr)
      {}

      void pushFront(T data)
      {
        Node< T > * ptr = new Node< T >(data);
        ptr->next_ = head_;
        if (head_ != nullptr)
        {
          head_->prev_ = ptr;
        }
        if (tail_ == nullptr)
        {
          tail_ = ptr;
        }
        head_ = ptr;
      }

      void pushBack(T data)
      {
        Node< T > * ptr = new Node< T >(data);
        ptr->prev_ = tail_;
        if (tail_ != nullptr)
        {
          tail_->next_ = ptr;
        }
        if (head_ == nullptr)
        {
          head_ = ptr;
        }
        tail_ = ptr;
      }

      void popFront()
      {
        if (head_ == nullptr)
        {
          return;
        }
        Node< T > * ptr = head_->next_;
        if (ptr != nullptr)
        {
          ptr->prev_ = nullptr;
        }
        tail_ = nullptr;
        delete head_;
        head_ = ptr;
      }

      void popBack()
      {
        if (tail_ == nullptr)
        {
          return;
        }
        Node< T > * ptr = tail_->prev_;
        if (ptr != nullptr)
        {
          ptr->next_ = nullptr;
        }
        head_ = nullptr;
        delete tail_;
        tail_ = ptr;
      }
    private:
      Node< T > * head_;
      Node< T > * tail_;
  };
}

#endif
