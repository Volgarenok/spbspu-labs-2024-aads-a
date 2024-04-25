#ifndef LIST_HPP
#define LIST_HPP

#include "constIterators.hpp"
#include "node.hpp"
#include "cstddef"

namespace skuratov
{
  template < typename T >
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

    List(size_t n, const T& value):
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      for (size_t i = 0; i < n; ++i)
      {
        pushBack(value);
      }
    }

    List< T > cbegin() noexcept
    {
      return ConstIterator< T >(head_);
    }

    List< T > cend() noexcept
    {
      return ConstIterator< T >(nullptr);
    }

    T & front()
    {
      return head_ -> value_;
    }

    T & back()
    {
      return tail_ -> value_;
    }

    bool empty() const
    {
      return !size_;
    }

    Node< T >* pushFront(T value)
    {
      Node< T >* ptr = new Node< T >(value);
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
      return ptr;
    }

    Node< T >* pushBack(T value)
    {
      Node< T >* ptr = new Node< T >(value);
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
      return ptr;
    }

    void popFront()
    {
      if (head_ == nullptr)
      {
        return;
      }
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

    void popBack()
    {
      if (tail_ == nullptr)
      {
        return;
      }
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

    void clear() noexcept
    {
      while (!empty())
      {
        popBack();
      }
      size_ = 0;
    }

    void assign(size_t n, const T& value)
    {
      clear();
      for (size_t i = 0; i < n; ++i)
      {
        push_back(value);
      }
    }

    void swap() noexcept
    {}

    void remove(const T& value)
    {}

    void remove_if()
    {}

    size_t getSize() const
    {
      return size_;
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}

#endif
