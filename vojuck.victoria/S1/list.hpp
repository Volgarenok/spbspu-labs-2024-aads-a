#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <iostream>
#include <cstddef>
#include "iterator.hpp"
#include "constiterator.hpp"
#include "node.hpp"

namespace vojuck
{
  template< typename T >
  class List
  {
    friend struct IteratorList< T >;
    friend struct ConstIteratorList< T >;
  public:
    using iterator = IteratorList< T >;
    using constiterator = ConstIteratorList< T >;

    List():
      head_(nullptr),
      size_(0)
    {}
    List(const List< T > & other):
      List()
    {
      details::Node< T >* current = other.head_;
      while (current)
      {
        push_front(current->data_);
        current = current->next_;
      }
      reverse();
      size_ = other.size_;
    }
    List(List && other) noexcept :
      head_(other.head_),
      size_(other.size_)
    {
      other->clear();
    }
    ~List()
    {
      clear();
    }

    List & operator=(const List< T > & other)
    {
      assert(this != &other);
      details::Node< T >* current = other.head_;
      while (current)
      {
        push_back(current->data);
        current = current->next;
      }
      size_ = other.size_;
      return *this;
    }
    List & operator=(List && other) noexcept
    {
      assert(this != &other);
      head_ = other.head_;
      size_ = other.size_;
      other->clear();
    }

    T & front()
    {
      return head_->data_;
    }

    iterator begin() noexcept
    {
      return iterator(head_);
    }
    iterator end() noexcept
    {
      return iterator(nullptr);
    }
    constiterator cbegin() const noexcept
    {
      return constiterator(head_);
    }
    constiterator cend() const noexcept
    {
      return constiterator(nullptr);
    }

    bool empty() const noexcept
    {
      return head_ == nullptr && size_ == 0;
    }
    void clear() noexcept
    {
      while(!empty())
      {
        pop_front();
      }
    }

    void push_front(const T & data_)
    {
      details::Node< T >* temp = new details::Node< T >(data_);
      temp->next_ = head_;
      head_ = temp;
      size_++;
    }
    void pop_front()
    {
      try
      {
        if (empty())
        {
          throw std::logic_error("empty list");
        }
        details::Node< T > temp = head_;
        head_ = nullptr;
        head_ = temp.next_;
        size_--;
      }
      catch (std::logic_error & e)
      {
        std::cout << e.what() << "\n";
      }
    }
    void swap(List< T > & other) noexcept
    {
      std::swap(size_, other.size_);
      std::swap(head_, other.head_);
    }
    void reverse() noexcept
    {
      if (empty()) return;

      constiterator it = cbegin();
      constiterator prev_it = cend();

      while (it != cend())
      {
        details::Node<T>* current = it.node_;

        current->next_ = prev_it.node_;

        prev_it = it;
        ++it;
      }

      head_ = prev_it.node_;
    }

  private:
    size_t size_;
    details::Node< T >* head_;
  };
}


#endif
