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
      List()
    {
      try
      {
        Node< T >* node = rhs.head_;
        while (size_ != rhs.size_)
        {
          push_back(node->value_);
          node = node->next_;
        }
        iterator_ = rhs.iterator_;
      }
      catch (const std::exception& e)
      {
        for (size_t j = 0; j < size_; ++j)
        {
          pop_front();
        }
        throw;
      }
    }
    List(const List< T >&& rhs)
    {
      swap(rhs);
    }
    List< T >& operator=(const List< T >&& rhs)
    {
      if (this != std::addressof(rhs))
      {
        clear();
        iterator_->node = nullptr;
        swap(rhs);
      }
      return *this;
    }
    List< T >& operator=(const List< T >& rhs)
    {
      if (this != std::addressof(rhs))
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
    void remove(const T& value)
    {
      Node< T >* node = head_;
      while (node->value_ != value)
      {
        node = node->next_;
      }
      if (node == head_)
      {
        pop_front();
      }
      else if (node == tail_)
      {
        pop_back();
      }
      else
      {
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        delete node;
        --size_;
      }
    }
    template< Functor >
    void remove_it(Functor f)
    {
      Node< T >* node = head_;
      while (node)
      {
        if (f(node))
        {
          if (node == head_)
          {
            pop_front();
          }
          else if (node == tail_)
          {
            pop_back();
          }
          else
          {
            node->next_->prev_ = node->prev_;
            node->prev_->next_ = node->next_;
            delete node;
            --size_;
           }
        }
      }
    }
    void swap(List< T >& list)
    {
      Node< T >* temp_head_ = head_;
      Node< T >* temp_tail_ = tail_;
      size_t temp_size_ = size_;
      ListIterator< T > temp_iterator_ = iterator_;
      head_ = list.head_;
      tail_ = list.tail_;
      size_ = list.size_;
      iterator_ = list.iterator_;
      list.head_ = temp_head_;
      list.tail_ = temp_tail_;
      list.size_ = temp_size_;
      list.iterator_ = temp_iterator_;
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
