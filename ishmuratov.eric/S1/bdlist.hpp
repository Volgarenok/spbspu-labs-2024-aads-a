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
        tail_(nullptr),
        size_(0)
      {}

      ~List()
      {
        clear();
      }

      List(const T & data, size_t size):
        List()
      {
        try
        {
          for (size_t i = 0; i < size; ++i)
          {
            pushBack(data);
          }
        }
        catch(const std::exception & e)
        {
          clear();
        }
      }

      List(const List & other):
        head_(nullptr),
        tail_(nullptr),
        size_(0)
      {
        try
        {
          Node< T > * cur = other.head_;
          while (size_ != other.size_)
          {
            pushBack(cur->data_);
            cur = cur->next_;
          }
        }
        catch (const std::exception & e)
        {
          clear();
        }
      }

      List(List && other):
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_)
      {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
      }

      Iterator< T > begin()
      {
        return Iterator< T >(head_);
      }

      const Iterator< T > cbegin() const
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end()
      {
        return Iterator< T >(tail_);
      }

      const Iterator< T > cend() const
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
        return head_ == nullptr && tail_ == nullptr;
      }

      size_t size() const
      {
        return size();
      }

      void assign(size_t count, const T & value)
      {
        clear();
        for (size_t i = 0; i < size; ++i)
        {
          pushBack(value);
        }
      }

      void assign(Iterator< T > first, Iterator< T > last)
      {
        clear();
        while (first != last)
        {
          pushBack(*first);
          ++first;
        }
      }

      void pushFront(const T & data)
      {
        Node< T > * ptr = new Node< T >(data);
        ptr->next_ = head_;
        if (tail_ == nullptr)
        {
          tail_ = ptr;
        }
        if (head_ != nullptr)
        {
          head_->prev_ = ptr;
        }
        head_ = ptr;
        ++size_;
      }

      void pushBack(const T & data)
      {
        Node< T > * ptr = new Node< T >(data);
        ptr->prev_ = tail_;
        if (head_ == nullptr)
        {
          head_ = ptr;
        }
        if (tail_ != nullptr)
        {
          tail_->next_ = ptr;
        }
        tail_ = ptr;
        ++size_;
      }

      void remove(const T & value)
      {
        if (empty())
        {
          return;
        }
        Node< T > * temp = head_;
        while (temp->data_ != value)
        {
          temp = temp->next;
        }
        if (temp == head_)
        {
          popFront();
        }
        else if (temp == tail_)
        {
          popBack();
        }
        else
        {
          temp->next_->prev_ = temp->prev_;
          temp->prev_->next_ = temp->next_;
          delete temp;
          --size_;
        }
      }

      template < class UnaryPredicate >
      void remove_if(UnaryPredicate p)
      {
        Node< T > * cur = head_;
        Node< T > * temp = nullptr;
        while (cur)
        {
          if (p(cur->data_))
          {
            if (cur == head_)
            {
              popFront();
              cur = head_;
            }
            else if(cur == tail_)
            {
              popBack();
              cur = tail_;
            }
            else
            {
              temp->next_ = cur->next_;
              delete cur;
              cur = temp->next;
              --size_;
            }
          }
          else
          {
            temp = cur;
            cur = cur->next;
          }
        }
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
        --size_;
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
        --size_;
      }

      void clear()
      {
        while (!empty())
        {
          popBack();
        }
        size_ = 0;
      }

      void swap(List< T > & other)
      {
        std::swap(other.head_, head_);
        std::swap(other.tail_, tail_);
      }

    private:
      Node< T > * head_;
      Node< T > * tail_;
      size_t size_;
  };
}

#endif
