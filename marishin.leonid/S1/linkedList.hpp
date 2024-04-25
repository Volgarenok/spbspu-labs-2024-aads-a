#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace marishin
{
  template < class T >
  class LinkedList
  {
  public:
    LinkedList():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    ~LinkedList()
    {
      clear();
    }

    LinkedList(const T & data, size_t size):
      LinkedList()
    {
      for (size_t i = 0; i < size; ++i)
      {
        push_back(data);
      }
    }

    LinkedList(const LinkedList & other):
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      try
      {
        detail::Node< T > * curr = other.head_;
        while (size_ != other.size_)
        {
          push_back(curr->data_);
          curr = curr->next_;
        }
      }
      catch (const std::exception & e)
      {
        clear();
        throw;
      }
    }

    LinkedList(LinkedList && other) noexcept:
      head_(other.head_),
      tail_(other.tail_),
      size_(other.size_)
    {
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }

    LinkedList & operator=(const LinkedList & other)
    {
      if (this != std::addressof(other))
      {
        LinkedList temp(other);
        swap(temp);
      }
      return *this;
    }

    LinkedList & operator=(LinkedList && other) noexcept
    {
      if (this != std::addressof(other))
      {
        clear();
        swap(other);
      }
      return *this;
    }

    Iterator< T > begin() noexcept
    {
      return Iterator< T >(head_);
    }

    Iterator< T > end() noexcept
    {
      return Iterator< T >(nullptr);
    }

    const Iterator< T > cbegin() const noexcept
    {
      return Iterator< T >(head_);
    }

    const Iterator< T > cend() const noexcept
    {
      return Iterator< T >(nullptr);
    }

    bool empty() const noexcept
    {
      return (head_ == nullptr) && (tail_ == nullptr);
    }

    T & front()
    {
      return head_->data_;
    }

    T & back()
    {
      return tail_->data_;
    }

    size_t size() const noexcept
    {
      return size_;
    }

    void assign(size_t count, const T & value)
    {
      LinkedList<T> ls;
      for (size_t i = 0; i < count; ++i)
      {
        ls.push_back(value);
      }
      swap(ls);
    }

    void push_front(const T & value)
    {
      detail::Node< T > * newNode = new detail::Node< T >(value);
      if (empty())
      {
        head_ = tail_ = newNode;
      }
      else
      {
        newNode->next_ = head_;
        head_->prev_ = newNode;
        head_ = newNode;
      }
      ++size_;
    }

    void pop_front()
    {
      detail::Node< T > * temp = head_->next_;
      if (temp != nullptr)
      {
        temp->prev_ = nullptr;
      }
      else
      {
        tail_ = nullptr;
      }
      delete head_;
      head_ = temp;
      --size_;
    }

    void push_back(const T & value)
    {
      detail::Node< T > * newNode = new detail::Node< T >(value);
      if (empty())
      {
        head_ = tail_ = newNode;
      }
      else
      {
        tail_->next_ = newNode;
        newNode->prev_ = tail_;
        tail_ = newNode;
      }
      ++size_;
    }

    void pop_back()
    {
      detail::Node< T > * temp = tail_->prev_;
      if (temp != nullptr)
      {
        temp->next_ = nullptr;
      }
      else
      {
        head_ = nullptr;
      }
      delete tail_;
      tail_ = temp;
      --size_;
    }

    void swap(LinkedList & other) noexcept
    {
      std::swap(other.head_, head_);
      std::swap(other.tail_, tail_);
    }

    void clear() noexcept
    {
      while (!empty())
      {
        pop_back();
      }
      size_ = 0;
    }

    void remove(const T & value)
    {
      remove_if(
        [&](const T & data)
        {
          return (data == value);
        }
      );
    }

    template < class Predicate >
    void remove_if(Predicate pred)
    {
      detail::Node< T > * curr = head_;
      detail::Node< T > * prev = nullptr;
      while (curr)
      {
        if (pred(curr->data_))
        {
          if (curr == head_)
          {
            pop_front();
            curr = head_;
          }
          else if (curr == tail_)
          {
            pop_back();
            curr = tail_;
          }
          else
          {
            prev->next_ = curr->next_;
            delete curr;
            curr = prev->next_;
            --size_;
          }
        }
        else
        {
          prev = curr;
          curr = curr->next_;
        }
      }
    }

  private:
    detail::Node< T >* head_;
    detail::Node< T >* tail_;
    size_t size_;
  };
}

#endif
