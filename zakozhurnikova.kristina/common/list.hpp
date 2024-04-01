#ifndef LIST_HPP
#define LIST_HPP
#include <utility>
#include <cstddef>
#include <string>
#include "node.hpp"
#include "iterator.hpp"
#include "functions.hpp"
#include "constIterator.hpp"

namespace zakozhurnikova
{
  template < typename T >
  using predicateFunction = bool (*)(T);

  template < typename T >
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    List(const List& rhs) :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      Node< T >* temp = rhs.head_;
      while (temp)
      {
        push_back(temp->data);
        temp = temp->next;
      }
    }

    List(List&& rhs) noexcept :
      head_(rhs.head_),
      tail_(rhs.tail_),
      size_(rhs.size_)
    {
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
      rhs.size_ = 0;
    }

    List& operator=(const List& rhs)
    {
      if (this != &rhs)
      {
        List temp(rhs);
        clear();
        head_ = temp.head_;
        tail_ = temp.tail_;
      }
      return *this;
    }

    List operator=(List&& rhs) noexcept
    {
      if (this != &rhs)
      {
        swap(rhs);
      }
      return this;
    }

    ~List()
    {
      clear();
    }

    T& front()
    {
      return head_->data;
    }

    void push_back(T data)
    {
      Node< T >* temp = new Node< T >{ data };

      if (!tail_)
      {
        tail_ = temp;
        head_ = temp;
      }
      else
      {
        tail_->next = temp;
        temp->prev = tail_;
        tail_ = temp;
      }
      ++size_;
    }

    void push_front(T data)
    {
      Node< T >* temp = new Node< T >{ data };
      if (!tail_)
      {
        head_ = temp;
        tail_ = temp;
      }
      else
      {
        head_->prev = temp;
        temp->next = head_;
        head_ = temp;
      }
      ++size_;
    }

    void pop_back() noexcept
    {
      Node< T >* toDelete = tail_;
      tail_ = tail_->prev;
      if (!tail_)
      {
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        tail_->next = nullptr;
      }
      delete toDelete;
      --size_;
    }

    void pop_front() noexcept
    {
      Node< T >* toDelete = head_;
      if(!head_->next)
      {
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        head_ = head_->next;
      }
      delete toDelete;
      --size_;
    }

    size_t size() const
    {
      return size_;
    }

    void clear() noexcept
    {
      while (head_)
      {
        pop_front();
      }
      tail_ = nullptr;
    }

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    void swap(List& rhs) noexcept
    {
      std::swap(head_, rhs.head_);
      std::swap(tail_, rhs.tail_);
      std::swap(size_, rhs.size_);
    }

    Iterator< T > begin() const
    {
      return Iterator< T >(head_);
    }

    Iterator< T > end() const
    {
      return Iterator< T >();
    }

    ConstIterator< T > cbegin() const
    {
      return ConstIterator< T >(head_);
    }

    ConstIterator< T > cend() const
    {
      return ConstIterator< T >();
    }

    void remove(const T& value)
    {
      Iterator< T > first = begin();
      Iterator< T > last = end();
      for (Iterator< T > it = first; it != last; ++it)
      {
        if (*it != value)
        {
          *first++ = std::move(*it);
        }
      }
    }

    void remove_if(predicateFunction< T > p)
    {
      auto first = begin();
      auto last = end();
      for (auto it = first; it != last; ++it)
      {
        if (!p(*(it)))
        {
          *first++ = std::move(*it);
        }
      }
    }

    void assign(Iterator< T > first, Iterator< T > last, const T& value)
    {
      fill(first, last, value);
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}

#endif
