#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"
#include "iterator.hpp"

namespace nikitov
{
  template< typename T >
  class Node;

  template< typename T >
  class List
  {
    friend class Node< T >;
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    ~List()
    {
      while (tail_->prev_ != nullptr)
      {
        Node< T >* ptr = tail_->prev_;
        delete tail_;
        tail_ = ptr;
      }
      delete tail_;
    }

    Node< T >* begin()
    {
      return head_;
    }
    Node< T >* end()
    {
      return tail_;
    }
    size_t size() const
    {
      return size_;
    }
    void push_back(T value)
    {
      Node< T >* ptr = new Node< T >(value);
      ptr->prev_ = tail_;
      if (tail_ != nullptr)
      {
        tail_->next_ = ptr;
      }
      else
      {
        head_ = ptr;
        tail_ = ptr;
      }
      tail_ = ptr;
      ++size_;
    }
    void pop_back()
    {
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
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
