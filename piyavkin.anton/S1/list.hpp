#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include "node.hpp"
#include "listiterator.hpp"

namespace piyavkin
{
  template< class T >
  class List
  {
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0),
      iterator_()
    {}
    ~List()
    {
      clear();
    }
    size_t size() const
    {
      return size_;
    }
    T& back() const
    {
      return tail_->value_;
    }
    T& front() const
    {
      return head_->value_;
    }
    ListIterator< T >& begin()
    {
      iterator_.node = head_;
      return iterator_;
    }
    ListIterator< T >& end()
    {
      iterator_.node = tail_;
      return iterator_;
    }
    void insert(ListIterator< T >& it, const T& value)
    {
      if (it == begin())
      {
        push_front(value);
      }
      else if (++it == end())
      {
        push_back(value);
      }
      else
      {
        --it;
        Node< T >* new_node = new Node< T >(value);
        new_node->next_ = it.node;
        new_node->prev_ = it.node->prev_;
        it.node->prev_ = new_node;
        new_node->prev_->next_ = new_node;
      }
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
//  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
    ListIterator< T > iterator_;
  };
}
#endif
