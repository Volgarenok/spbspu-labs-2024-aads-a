#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include "node.hpp"

namespace piyavkin
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
    size_t size() const
    {
      return size_;
    }
    bool empty() const
    {
      return size_ == 0;
    }
    void push_front(const T& value)
    {
      Node< T >* new_node = new Node< T >(value);
      new_node->next_ = head_;
      if (head_)
      {
        head_->prev_ = new_node;
      }
      if (!tail_)
      {
        tail_ = new_node;
      }
      head_ = new_node;
      ++size_;
    }
    void push_back(const T& value)
    {
      Node< T >* new_node = new Node< T >(value);
      new_node->prev_ = tail_;
      if (tail_)
      {
        tail_->next_ = new_node;
      }
      if (!head_)
      {
        head_ = new_node;
      }
      tail_ = new_node;
      ++size_;
    }
    void pop_back()
    {
      if (empty())
      {
        throw std::logic_error("The list is empty");
      }
      else if (size_ == 1)
      {
        delete tail_;
        --size_;
      }
      else
      {
        tail_ = tail_->prev_;
        delete tail_->next_;
        --size_;
      }
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::logic_error("The list is empty");
      }
      else if (size_ == 1)
      {
        delete head_;
        --size_;
      }
      else
      {
        head_ = head_->next_;
        delete head_->prev_;
        --size_;
      }
    }
    void clear()
    {
      while (size() != 0)
      {
        pop_back();
      }
    }
    template< class D >
    class ListIterator
    {
    public:
      ListIterator():
        node(nullptr)
      {}
      ListIterator(const ListIterator< D >&) = default;
      ListIterator< D > operator=(const ListIterator< D >&) = default;
      ~ListIterator() = default;
      ListIterator< D > operator++()
      {
        node = node->next_;
        return *this;
      }
      ListIterator< D > operator--()
      {
        node = node->prev_;
        return *this;
      }
      ListIterator< D > operator++(int)
      {
        ListIterator< D > result(*this);
        ++(*this);
        return result;
      }
      ListIterator< D > operator--(int)
      {
        ListIterator< D > result(*this);
        --(*this);
        return result;
      }
      bool operator==(const ListIterator< D >& rhs) const
      {
        return node == rhs.node;
      }
      bool operator!=(const ListIterator< D >& rhs) const
      {
        return !(*this == rhs);
      }
      D* operator->()
      {
        return std::addressof(node->value_);
      }
      D& operator*()
      {
        return node->value_;
      }
    private:
      Node< D >* node;
    };
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
