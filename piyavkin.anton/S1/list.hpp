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
    List(const List< T >& rhs):
      size_(rhs.size_),
      iterator_(rhs.iterator_)
    {
      size_t i = 1;
      try
      {
        head_ = new Node< T >(rhs.head_->value_);
        Node< T >* node = head_;
        while (i < rhs.size() - 1)
        {
          node->next_ = new Node< T >(get_element(i++));
        }
        tail_ = new Node< T >(rhs.tail_->value_);
      }
      catch (const std::exception& e)
      {
        for (size_t j = 0; j < i; ++j)
        {
          pop_front();
        }
        throw;
      }
    }
    List< T > operator=(const List< T >& rhs)
    {
      if (this != &rhs)
      {
        List< T > temp(rhs);
        temp.swap(*this);
      }
      return *this;
    }
    ~List()
    {
      clear();
    }
    void swap(List< T >& list)
    {
      List< T > temp;
      temp->head_ = head_;
      temp->tail_ = tail_;
      temp->size_ = size_;
      temp->iterator_ = iterator_;
      head_ = list->head_;
      tail_ = list->tail_;
      size_ = list->size_;
      iterator_ = list->iterator_;
      list->head_ = temp->head_;
      list->tail_ = temp->tail_;
      list->size_ = temp->size_;
      list->iterator_ = temp->iterator_;
    }
    T& get_element(size_t i)
    {
      iterator_.node = head_;
      for (size_t j = 0; j < i; ++j)
      {
        ++iterator_;
      }
      return iterator_.node->value_;
    }
    void out_val(std::ostream& out, size_t i, size_t& sum)
    {
      if (!head_)
      {
        throw std::logic_error("error");
      }
      if (i < size())
      {
        iterator_.node = head_;
        for (size_t j = 0; j < i; ++j)
        {
          ++iterator_;
        }
        if (i < size())
        {
          sum += iterator_.node->value_;
          out << iterator_.node->value_;
        }
      }
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
    void erase(ListIterator< T > it)
    {
      if (it == begin())
      {
        pop_front();
      }
      else if (it == end())
      {
        pop_back();
      }
      else
      {
        it.node->next_->prev_ = it.node->prev_;
        it.node->prev_->next_ = it.node->next_;
        delete it.node;
        --size_;
      }
    }
    void erase(ListIterator< T >& it_start, ListIterator< T >& it_finish)
    {
      while (it_start != it_finish)
      {
        erase(it_start++);
      }
      erase(it_start);
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
        ++size_;
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
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
    ListIterator< T > iterator_;
  };
}
#endif
