#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

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

      List(ConstIterator< T > begin, ConstIterator< T > end):
        head_(new Node< T >),
        tail_(head_)
      {
        for (auto i = begin; i != end; i++)
        {
          push_back(*i);
        }
      }

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

      List(List< T >&& other):
        head_(other.head_)
      {}

      List(size_t n, const T& value):
        head_(nullptr),
        tail_(head_)
      {
        assign(n, value);
      }

      List(std::initializer_list< T > init):
        head_(new Node< T >),
        tail_(head_)
      {
        for (T it : init)
        {
          push_back(it);
        }
      }

      ~List()
      {
        clear();
      }

      void assign(size_t n, const T& value)
      {
        clear();
        for (size_t i = 0; i < n; i++)
        {
          push_back(value);
        }
      }

      void assign(std::initializer_list< T > init)
      {
        clear();
        for (T it : init)
        {
          push_back(it);
        }
      }



      void swap(List& other)
      {
        Node< T >* temp = other.head_;
        other.head_ = head_;
        head_ = temp;
      }

      Iterator< T > insert(ConstIterator< T > pos, const T& value)
      {
        if (pos == begin())
        {
          push_front(value);
          return begin();
        }
        if (pos == end())
        {
          push_back(value);
          return end();
        }
        else
        {
          Node< T >* new_node = new Node< T >(value);
          Node< T >* next_node = pos->node_->next_;
          pos->node_->next_ = new_node;
          next_node->prev_ = new_node;
          new_node->next_ = next_node;
          new_node->prev_ = pos->node_;
        }
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
        tail_ = nullptr;
      }

      void remove(const T& value)
      {
        for (auto it = begin(); it != end(); it++)
        {
          if (*it == value)
          {
            if (it == begin())
            {
              pop_front();
              return;
            }
            if (it == end())
            {
              pop_back();
              return;
            }
            it->prev_->next_ = it->next_;
            it->next_prev_ = it->prev_;
            delete *it;
          }
        }
      }

      template< class P >
      void remove_if (P predicate)
      {
        for (auto it = begin(); it != end(); it++)
        {
          if (predicate(it))
          {
            if (it == begin())
            {
              pop_front();
              return;
            }
            if (it == end())
            {
              pop_back();
              return;
            }
            it->prev_->next_ = it->next_;
            it->next_prev_ = it->prev_;
            delete *it;
          }
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

      ConstIterator< T > cbegin() const
      {
        return ConstIterator< T >(head_);
      }

      ConstIterator< T > cend() const
      {
        return ConstIterator< T >(nullptr);
      }

    private:
      Node< T >* head_;
      Node< T >* tail_;
  };
}
#endif
