#ifndef LIST_HPP
#define LIST_HPP

#include <utility>
#include <algorithm>
#include <cstddef>
#include "node.hpp"
#include "constIterators.hpp"

namespace skuratov
{
  template< typename T >
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
        while (head_ != nullptr)
        {
          popFront();
        }
      }

      List(const T& value, size_t n):
        head_(nullptr),
        tail_(nullptr),
        size_(0)
      {
        try
        {
          for (size_t i = 0; i < n; ++i)
          {
            pushBack(value);
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }

      List(const List& diff):
        head_(nullptr),
        tail_(nullptr),
        size_(0)
      {
        try
        {
          detail::Node< T >* current = diff.head_;
          while (current)
          {
            pushBack(current->value_);
            current = current->next_;
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }

      List& operator=(const List& diff)
      {
        if (this != std::addressof(diff))
        {
          List tempList(diff);
          swap(tempList);
        }
        return *this;
      }

      List(List&& diff) noexcept:
        head_(diff.head_),
        tail_(diff.tail_),
        size_(diff.size_)
      {
        diff.head_ = nullptr;
        diff.tail_ = nullptr;
        diff.size_ = 0;
      }

      List& operator=(List&& diff)
      {
        if (this != std::addressof(diff))
        {
          clear();
          swap(diff);
        }
        return *this;
      }

      ConstIterator< T > cbegin() const noexcept
      {
        return ConstIterator< T >(head_);
      }

      ConstIterator< T > cend() const noexcept
      {
        return ConstIterator< T >(nullptr);
      }

      T& front()
      {
        return head_->value_;
      }

      const T& front() const
      {
        return head_->value_;
      }

      T& back()
      {
        return tail_->value_;
      }

      const T& back() const
      {
        return tail_->value_;
      }

      bool empty() const noexcept
      {
        return !size_;
      }

      void pushFront(const T& value)
      {
        detail::Node< T >* ptr = new detail::Node< T >(value);
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
        ++size_;
      }

      void pushBack(const T& value)
      {
        detail::Node< T >* ptr = new detail::Node< T >(value);
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
        ++size_;
      }

      void popFront()
      {
        if (head_ == nullptr)
        {
          return;
        }
        detail::Node< T >* ptr = head_->next_;
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
        if (tail_ == nullptr)
        {
          return;
        }
        detail::Node< T >* ptr = tail_->prev_;
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
          popFront();
        }
      }

      void assign(size_t n, const T& value)
      {
        clear();
        for (size_t i = 0; i < n; ++i)
        {
          pushBack(value);
        }
      }

      void swap(List& diff)
      {
        std::swap(head_, diff.head_);
        std::swap(tail_, diff.tail_);
        std::swap(size_, diff.size_);
      }

      void remove(const T& value)
      {
        detail::Node< T > dummyNode;
        dummyNode.next_ = head_;
        detail::Node< T >* prev_ = std::addressof(dummyNode);
        detail::Node< T >* current = head_;

        while (current)
        {
          if (current->data == value)
          {
            prev_->next_ = current->next_;
            delete current;
            current = prev_->next_;
          }
          else
          {
            prev_ = current;
            current = current->next_;
          }
        }
        head_ = dummyNode.next_;
      }

      template< typename UnaryPredicate >
      void removeIf(UnaryPredicate predicate)
      {
        detail::Node< T > dummyNode;
        dummyNode.next_ = head_;
        detail::Node< T >* prev_ = std::addressof(dummyNode);
        detail::Node< T >* current = head_;

        while (current)
        {
          if (predicate(current->value_))
          {
            prev_->next_ = current->next_;
            delete current;
            current = prev_->next_;
          }
          else
          {
            prev_ = current;
            current = current->next_;
          }
        }
        head_ = dummyNode.next_;
      }

      size_t getSize() const
      {
        return size_;
      }

    private:
      detail::Node< T >* head_;
      detail::Node< T >* tail_;
      size_t size_;
  };
}

#endif
