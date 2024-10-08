#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>

#include "node.h"
#include "iterator.h"

namespace serter
{
  template < typename T >
  class Doubly_linked_list
  {
  public:
    Doubly_linked_list():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    Doubly_linked_list(const Doubly_linked_list< T >& obj):
      Doubly_linked_list{}
    {
      auto objIt = obj.begin();
      while (objIt != obj.end())
      {
        push(*objIt);
        ++objIt;
      }
    }
    Doubly_linked_list(Doubly_linked_list< T >&& obj):
      Doubly_linked_list{}
    {
      head_ = obj.head_;
      tail_ = obj.tail_;
      size_ = obj.size_;
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    }
    Doubly_linked_list& operator=(const Doubly_linked_list& obj)
    {
      Doubly_linked_list temp(obj);
      std::swap(temp, *this);
      return *this;
    }
    Doubly_linked_list& operator=(Doubly_linked_list&& obj)
    {
      Doubly_linked_list temp(obj);
      std::swap(temp, *this);
      return *this;
    }
    bool is_empty()
    {
      return size_ == 0;
    }
    T get_front()
    {
      return head_->data_;
    }
    T get_back()
    {
      return tail_->data_;
    }
    size_t get_size()
    {
      return size_;
    }
    void push(const T& value)
    {
      Node< T >* new_node = new Node< T >(value, nullptr);
      if (!head_)
      {
        head_ = new_node;
        tail_ = new_node;
      }
      else
      {
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
        tail_ = new_node;
      }
      ++size_;
    }
    void pop_back()
    {
      if (!head_)
      {
        std::out_of_range("List is empty bruuhh");
      }
      if (head_ == tail_)
      {
        delete tail_;
        head_ = tail_ = nullptr;
      }
      else
      {
        Node< T >* temp = tail_->prev_;
        delete tail_;
        tail_ = temp;
        tail_->next_ = nullptr;
      }
      --size_;
    }
    void pop_front()
    {
      if (head_ == tail_)
      {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        Node< T >* temp = head_->next_;
        delete head_;
        head_ = temp;
        head_->prev_ = nullptr;
      }
      size_--;
    }
    void swap(size_t pos_1, size_t pos_2)
    {
      if (pos_1 < 0 || pos_1 >= size_ || pos_2 < 0 || pos_2 >= size_)
      {
        throw std::out_of_range("Index out of range :(");
      }
      T& data_1 = (*this)[pos_1];
      T& data_2 = (*this)[pos_2];
      T temp = data_1;
      data_1 = data_2;
      data_2 = temp;
    }
    void clear()
    {
      while (!is_empty())
      {
        pop_back();
      }
      tail_ = nullptr;
      size_ = 0;
    }
    Iterator< T > begin() const
    {
      return Iterator< T >(head_);
    }
    Iterator< T > end() const
    {
      return Iterator< T >(nullptr);
    }
    ~Doubly_linked_list()
    {
      clear();
    };
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}

#endif
