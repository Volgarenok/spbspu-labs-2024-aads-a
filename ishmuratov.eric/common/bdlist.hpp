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
        for (size_t i = 0; i < size; ++i)
        {
          pushBack(data);
        }
      }

      List(const List & other):
        head_(nullptr),
        tail_(nullptr),
        size_(0)
      {
        try
        {
          detail::Node< T > * cur = other.head_;
          while (size_ != other.size_)
          {
            pushBack(cur->data_);
            cur = cur->next_;
          }
        }
        catch (const std::exception & e)
        {
          clear();
          throw;
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

      List & operator=(const List & other)
      {
        List temp(other);
        swap(temp);
        return *this;
      }

      List & operator=(List && other)
      {
        clear();
        swap(other);
        return *this;
      }

      Iterator< T > begin() noexcept
      {
        return Iterator< T >(head_);
      }

      const Iterator< T > cbegin() const noexcept
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end() noexcept
      {
        return Iterator< T >(nullptr);
      }

      const Iterator< T > cend() const noexcept
      {
        return Iterator< T >(nullptr);
      }

      T & front()
      {
        return head_->data_;
      }

      T & back()
      {
        return tail_->data_;
      }

      bool empty() const noexcept
      {
        return head_ == nullptr && tail_ == nullptr;
      }

      size_t size() const noexcept
      {
        return size_;
      }

      void assign(size_t count, const T & value)
      {
        List temp;
        clear();
        for (size_t i = 0; i < count; ++i)
        {
          temp.pushBack(value);
        }
        swap(temp);
      }

      void pushFront(const T & data)
      {
        detail::Node< T > * ptr = new detail::Node< T >(data);
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
        detail::Node< T > * ptr = new detail::Node< T >(data);
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
        auto predicate =
          [& value](const T & data_)
          {
            return data_ == value;
          };
        remove_if(predicate);
      }

      template < class UnaryPredicate >
      void remove_if(UnaryPredicate p)
      {
        detail::Node< T > * cur = head_;
        detail::Node< T > * temp = nullptr;
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
              cur = temp->next_;
              --size_;
            }
          }
          else
          {
            temp = cur;
            cur = cur->next_;
          }
        }
      }

      void popFront()
      {
        if (empty())
        {
          return;
        }
        detail::Node< T > * ptr = head_->next_;
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

      void popBack()
      {
        if (empty())
        {
          return;
        }
        detail::Node< T > * ptr = tail_->prev_;
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

      void clear() noexcept
      {
        while (!empty())
        {
          popBack();
        }
        size_ = 0;
      }

      void swap(List & other)
      {
        std::swap(other.head_, head_);
        std::swap(other.tail_, tail_);
      }

    private:
      detail::Node< T > * head_;
      detail::Node< T > * tail_;
      size_t size_;
  };
}

#endif
