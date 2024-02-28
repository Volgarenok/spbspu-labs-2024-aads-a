#ifndef BDLIST_HPP
#define BDLIST_HPP

#include <algorithm>
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

      ~List()
      {
        clear();
      }

      Iterator< T > begin()
      {
        return Iterator< T >(head_);
      }

      const Iterator< T > begin() const
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end()
      {
        return Iterator< T >(tail_);
      }

      const Iterator< T > end() const
      {
        return Iterator< T >(tail_);
      }

      T & front()
      {
        return head_->data_;
      }

      T & back()
      {
        return tail_->data_;
      }

      bool empty() const
      {
        return begin() == end();
      }

      void pushFront(const T & data)
      {
        Node< T > * ptr = new Node< T >(data);
        ptr->next_ = head_;
        head_ = ptr;
      }

      void pushBack(const T & data)
      {
        Node< T > * ptr = new Node< T >(data);
        ptr->prev_ = tail_;
        tail_ = ptr;
      }

      void popFront()
      {
        if (empty())
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
        if (empty())
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

      void clear()
      {
        while (!empty())
        {
          popBack();
        }
      }

      void swap(List< T > & other)
      {
        std::swap(other.head_, head_);
        std::swap(other.tail_, tail_);
      }

    private:
      Node< T > * head_;
      Node< T > * tail_;
  };
}

#endif
