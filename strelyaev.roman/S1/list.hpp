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
        head_(nullptr),
        tail_(nullptr)
      {
        assign(begin, end);
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

      void assign(Iterator< T > begin, Iterator< T > end)
      {
        clear();
        while (begin != end)
        {
          push_back(*begin);
          ++begin;
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
          Node< T >* new_node = new Node< T >(value);
          Node< T >* next_node = pos->node_->next_;
          pos->node_->next_ = new_node;
          next_node->prev_ = new_node;
          new_node->next_ = next_node;
          new_node->prev_ = pos->node_;
      }

      void splice(Iterator< T > pos, List< T >& other)
      {
        if (&other == this)
        {
          return;
        }
        if (other.empty())
        {
          return;
        }
        Node< T >* current = pos.get_node();
        current->next_->last_ = other.tail_;
        other.tail_->next_ = current->next_;
        current->next_ = other.head_;
        other.head_->last_ = current;
        other.head_ = nullptr;
        other.tail_ = nullptr;
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

      Iterator< T > erase(Iterator< T > pos)
      {
        if (pos == begin())
        {
          pop_front();
          return ++pos;
        }
        if (pos == end())
        {
          pop_back();
          return end();
        }
        auto next_it = pos;
        next_it++;
        pos.get_node()->next_->prev_ = pos.get_node()->prev_;
        pos.get_node()->prev_->next_ = pos.get_node()->next_;
        delete pos.get_node();
        return next_it;
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

      List< T >& operator=(const List< T > other)
      {
        if (this == &other)
        {
          return *this;
        }
        assign(other.begin(), other.end());
      }

      bool operator==(const List< T >& other) const
      {
        size_t size_this = 0;
        size_t size_other = 0;
        for (auto it = begin(); it != end(); it++, size_this++)
        for (auto it = other.begin(); it != other.end(); it++, size_other++);
        if (size_this != size_other)
        {
          return false;
        }
        auto this_it = begin();
        auto other_it = other.begin();
        for (this_it; this_it != end(); this_it++, other_it++)
        {
          if (*this_it != *other_it)
          {
            return false;
          }
        }
        return true;
      }

      bool operator!=(const List< T >& other) const
      {
        return !(*this == other);
      }

      bool operator<(const List< T >& other) const
      {
        size_t size_this = 0;
        size_t size_other = 0;
        for (auto it = begin(); it != end(); it++, size_this++)
        for (auto it = other.begin(); it != other.end(); it++, size_other++);
        if (size_this < size_other)
        {
          return true;
        }
        return false;
      }

      bool operator>(const List< T >& other) const
      {
        return other < *this;
      }

      bool operator<=(const List< T >& other) const
      {
        return (*this < other) || (*this == other);
      }

      bool operator>=(const List< T >& other) const
      {
        return (*this > other) || (*this == other);
      }

    private:
      Node< T >* head_;
      Node< T >* tail_;
  };
}
#endif
