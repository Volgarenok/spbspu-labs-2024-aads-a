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
      Node< T > * node = new Node< T >(val, nullptr, tail_);
      if ((head_ == nullptr) && (tail_ == nullptr))
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
    void push_front(const T & val)
    {
      Node< T > * node = new Node< T >(val, head_, nullptr);
      if ((head_ == nullptr) && (tail_ == nullptr))
      {
        head_ = node;
        tail_ = node;
      }
      else
      {
        node->next_ = head_;
        head_->prev_ = node;
        head_ = node;
      }
      ++size_;
    }

    void pop_back()
    {

      if (tail_ == nullptr)
      {
        return;
      }
      Node< T > * newtail = tail_->prev_;
      if (newtail)
      {
        newtail->next_ = nullptr;
      }
      else
      {
        head_ = nullptr;
      }
      delete tail_;
      tail_ = newtail;
      --size_;
    }
    void pop_front()
    {
      if (head_ == nullptr)
      {
        return;
      }
      Node< T > * newhead = head_->next_;
      if (newhead)
      {
        newhead->prev_ = nullptr;
      }
      else
      {
        tail_ = nullptr;
      }
      delete head_;
      head_ = newhead;
      --size_;
    }
    void clear()
    {
      while (tail_)
      {
        pop_back();
      }
    }

    void swap(List< T > & list)
    {
      std::swap(list.head_, head_);
      std::swap(list.tail_, tail_);
      std::swap(list.size_, size_);
    }


    void outputList(std::ostream & out) const
    {
      Node< T > * head = head_;
      while (head != nullptr)
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
