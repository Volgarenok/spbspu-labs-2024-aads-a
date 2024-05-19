#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <string>
#include <utility>
#include "constIterator.hpp"
#include "iterator.hpp"
#include "node.hpp"

namespace zakozhurnikova
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

    List(const List& rhs):
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      detail::Node< T >* temp = rhs.head_;
      while (temp)
      {
        try
        {
          push_back(temp->data);
          temp = temp->next;
        }
        catch (...)
        {
          clear();
          throw;
        }
      }
    }

    List(List&& rhs) noexcept:
      head_(rhs.head_),
      tail_(rhs.tail_),
      size_(rhs.size_)
    {
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
      rhs.size_ = 0;
    }

    template < typename InputIt >
    List(InputIt first, InputIt last):
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      while(first != last)
      {
        try
        {
          push_back(*first);
          ++first;
        }
        catch (...)
        {
          clear();
          throw;
        }
      }
    }

    List& operator=(const List& rhs)
    {
      if (this != std::addressof(rhs))
      {
        List temp(rhs);
        swap(temp);
      }
      return *this;
    }

    List& operator=(List&& rhs) noexcept
    {
      if (this != std::addressof(rhs))
      {
        clear();
        swap(rhs);
      }
      return *this;
    }

    ~List()
    {
      clear();
    }

    T& front()
    {
      return head_->data;
    }

    const T& front() const
    {
      return head_->data;
    }

    T& back()
    {
      return tail_->data;
    }

    const T& back() const
    {
      return tail_->data;
    }

    void push_back(const T& data)
    {
      detail::Node< T >* temp = new detail::Node< T >{ data };

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

    void push_front(const T& data)
    {
      detail::Node< T >* temp = new detail::Node< T >{ data };
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
      detail::Node< T >* toDelete = tail_;
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
      detail::Node< T >* toDelete = head_;
      if (!head_->next)
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
      while (!empty())
      {
        pop_front();
      }
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

    Iterator< T > begin() const noexcept
    {
      return Iterator< T >(head_);
    }

    Iterator< T > end() const noexcept
    {
      return Iterator< T >();
    }

    ConstIterator< T > cbegin() const noexcept
    {
      return ConstIterator< T >(head_);
    }

    ConstIterator< T > cend() const noexcept
    {
      return ConstIterator< T >();
    }

    void remove(const T& value)
    {
      remove_if([&](const T& item) { return (item == value); });
    }

    template < class UnaryPredicate >
    void remove_if(UnaryPredicate p)
    {
      if (empty())
      {
        return;
      }
      auto last = end();
      auto it = begin();
      if (p(*begin()))
      {
        pop_front();
      }
      while (it != last)
      {
        if (p(*it))
        {
          detail::Node< T >* toDelete = it;
          it->prev->next = it->next;
          if (it->next != nullptr)
          {
            it->next->prev = it->prev;
          }
          ++it;
          delete toDelete;
        }
      }
    }

    void assign(size_t count, const T& value)
    {
      List< T > temp;
      for (size_t i = 0; i < count; i++)
      {
        temp.push_front(value);
      }
      swap(temp);
    }

  private:
    detail::Node< T >* head_;
    detail::Node< T >* tail_;
    size_t size_;
  };
}

#endif
