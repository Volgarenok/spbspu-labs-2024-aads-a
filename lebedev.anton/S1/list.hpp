#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"

namespace lebedev
{
  template< class T >
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    size_t size() const
    {
      return size_;
    }
    bool empty() const
    {
      return size_ == 0;
    }

    void push_back(const T & val)
    {
      Node< T > * node = new Node< T >(val);
      if (head_ == nullptr)
      {
        head_ = node;
        tail_ = node;
      }
      else
      {
        node->prev_ = tail_;
        tail_->next_ = node;
        tail_ = node;
      }
      ++size_;
    }

    void outputList(std::ostream & out) const
    {
      Node< T > * head = head_;
      while (head)
      {
        out << head->data_ << '\n';
        head = head->next_;
      }
    }


  private:
    Node< T > * head_;
    Node< T > * tail_;
    size_t size_;
  };
}

#endif
