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
      tail_ = tail_->prev_;
      delete tail_->next_;
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
      tail_ = new Node< T >(value, tail_, nullptr);
      ++size_;
    }
    void pop_back()
    {
      tail_ = tail_->prev_;
      delete tail_->next_;
      tail_->next_ = nullptr;
      --size_;
    }
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
#endif
