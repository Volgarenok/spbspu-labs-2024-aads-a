#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include "iterator.hpp"

namespace strelyaev
{
  template< typename T >
  class List
  {
    public:
      List(Node< T >* head, Node< T >* tail):
        head_(head),
        tail_(tail)
      {}

      List():
        head_(nullptr),
        tail_(nullptr)
      {}

      List(const List& other):
        head_(nullptr),
        tail_(nullptr)
      {
        for (auto it = other.head_; it != nullptr; it = it->next_)
        {
          push_back(it->value_);
        }
      }

      ~List()
      {
        clear();
      }

      void swap(List& other)
      {
        Node< T >* temp = other.head_;
        other.head_ = head_;
        head_ = temp;
      }

      bool empty()
      {
        return head_ == nullptr;
      }

      void push_back(const T& val)
      {
        Node< T >* new_node = new Node< T >(val);
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
      }

      void push_front(const T& val)
      {
        Node< T >* new_node = new Node< T >(val);
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
      }

      void pop_front()
      {
        if (!head_)
        {
          return;
        }
        Node< T >* temp = head_;
        head_ = head_->next_;
        if (head_)
        {
          head_->prev_ = nullptr;
        }
        delete temp;
      }

      void pop_back()
      {
        if (!tail_)
        {
          return;
        }
        Node< T >* temp = tail_;
        tail_ = tail_->prev_;
        if (tail_)
        {
          tail_->next_ = nullptr;
        }
        delete temp;
      }

      T& back() const
      {
        return tail_->value_;
      }

      T& front() const
      {
        return head_->value_;
      }

      void clear()
      {
        while (head_ != nullptr)
        {
          pop_front();
        }
      }

      Iterator< T > begin()
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end()
      {
        return Iterator< T >(nullptr);
      }

    private:
      Node< T >* head_;
      Node< T >* tail_;
  };
}
#endif
