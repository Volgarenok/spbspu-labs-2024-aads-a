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
      List();
      List(const List& other);
      List(List< T >&& other);
      List(size_t n, const T& value);
      List(std::initializer_list< T > init);
      List(ConstIterator< T > begin, ConstIterator< T > end);
      ~List();

      void assign(size_t n, const T& value);
      void assign(std::initializer_list< T > init);
      void assign(Iterator< T > begin, Iterator< T > end);
      void swap(List& other);

      Iterator< T > insert(ConstIterator< T > pos, const T& value);
      void splice(Iterator< T > pos, List< T >& other);

      bool empty();
      void push_back(const T& val);
      void push_front(const T& val);
      Iterator< T > erase(Iterator< T > pos);
      void pop_front();
      void pop_back();
      T& back() const;
      T& front() const;
      void clear();
      void remove(const T& value);
      template< class P > void remove_if (P predicate);
      void reverse();

      Iterator< T > begin();
      Iterator< T > end();
      ConstIterator< T > cbegin() const;
      ConstIterator< T > cend() const;

      List< T >& operator=(const List< T > other);
      bool operator==(const List< T >& other) const;
      bool operator!=(const List< T >& other) const;
      bool operator<(const List< T >& other) const;
      bool operator>(const List< T >& other) const;
      bool operator<=(const List< T >& other) const;
      bool operator>=(const List< T >& other) const;



    private:
      Node< T >* head_;
      Node< T >* tail_;
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  List< T >::List(const List& other):
    head_(nullptr),
    tail_(nullptr)
  {
    for (auto it = other.head_; it != nullptr; it = it->next_)
    {
      push_back(it->value_);
    }
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    head_(other.head_),
    tail_(other.tail_)
  {}

  template< typename T >
  List< T >::List(size_t n, const T& value):
    head_(nullptr),
    tail_(nullptr)
  {
    assign(n, value);
  }

  template< typename T >
  List< T >::List(std::initializer_list< T > init):
    head_(new Node< T >),
    tail_(head_)
  {
    for (T it : init)
    {
      push_back(it);
    }
  }

  template< typename T >
  List< T >::List(ConstIterator< T > begin, ConstIterator< T > end):
    head_(nullptr),
    tail_(nullptr)
  {
    assign(begin, end);
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  void List< T >::assign(size_t n, const T& value)
  {
    clear();
    for (size_t i = 0; i < n; i++)
    {
      push_back(value);
    }
  }

  template< typename T >
  void List< T >::assign(std::initializer_list< T > init)
  {
    clear();
    for (T it : init)
    {
      push_back(it);
    }
  }

  template< typename T >
  void List< T >::assign(Iterator< T > begin, Iterator< T > end)
  {
    clear();
    while (begin != end)
    {
      push_back(*begin);
      ++begin;
    }
  }

  template< typename T >
  void List< T >::swap(List& other)
  {
    Node< T >* temp = other.head_;
    other.head_ = head_;
    head_ = temp;
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > pos, const T& value)
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

  template< typename T >
  void List< T >::splice(Iterator< T > pos, List< T >& other)
  {
    if ((&other == this) || other.empty())
    {
      return;
    }
    Node< T >* before = pos->prev;
    if (pos == begin())
    {
      head_->prev_ = other.tail_;
      other.tail_ = head_;
      head_ = other.head_;
      return;
    }
    if (pos == end())
    {
      tail_->next_ = other.head_;
      other.head_->prev_ = tail_;
      tail_ = other.tail_;
      return;
    }
    pos.node_->prev_->next_ = other.head_;
    other.tail_->next_ = pos.node_;
    other.head_->prev_ = pos.node_->prev_;
    pos.node_->prev_ = other.tail_;
    other.clear();
    return;
  }

  template< typename T >
  bool List< T >::empty()
  {
    return head_ == nullptr;
  }

  template< typename T >
  void List< T >::push_back(const T& val)
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

  template< typename T >
  void List< T >::push_front(const T& val)
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

  template< typename T >
  Iterator< T > List< T >::erase(Iterator< T > pos)
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
    pos->prev_->next_ = pos->next_;
    pos->next_->prev_ = pos->prev_;
    delete pos.node_;
  }

  template< typename T >
  void List< T >::pop_front()
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

  template< typename T >
  void List< T >::pop_back()
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

  template< typename T >
  T& List< T >::back() const
  {
    return tail_->value_;
  }

  template< typename T >
  T& List< T >::front() const
  {
    return head_->value_;
  }

  template < typename T >
  void List< T >::clear()
  {
    while (head_ != nullptr)
    {
      pop_front();
    }
    tail_ = nullptr;
  }

  template< typename T >
  void List< T >::remove(const T& value)
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

  template< typename T >
  template< typename P >
  void List< T >::remove_if (P predicate)
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

  template< typename T >
  void List< T >::reverse()
  {
    if (empty())
    {
      return;
    }
    Node< T >* current = head_;
    Node< T >* temp = nullptr;
     while (current != nullptr)
     {
      temp = current->prev_;
      current->prev_ = current->next_;
      current->next_ = temp;
      current = current->prev_;
    }
    temp = head_;
    head_ = tail_;
    tail_ = temp;
  }

  template< typename T >
  Iterator< T > List< T >::begin()
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Iterator< T > List< T >::end()
  {
    return Iterator< T >(nullptr);
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >(nullptr);
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T > other)
  {
    if (this == &other)
    {
      return *this;
    }
    assign(other.begin(), other.end());
  }

  template< typename T >
  bool List< T >::operator==(const List< T >& other) const
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

  template< typename T >
  bool List< T >::operator!=(const List< T >& other) const
  {
    return !(*this == other);
  }

  template< typename T >
  bool List< T >::operator<(const List< T >& other) const
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

  template< typename T >
  bool List< T >::operator>(const List< T >& other) const
  {
    return other < *this;
  }

  template< typename T >
  bool List< T >::operator<=(const List< T >& other) const
  {
    return (*this < other) || (*this == other);
  }

  template< typename T >
  bool List< T >::operator>=(const List< T >& other) const
  {
    return (*this > other) || (*this == other);
  }

}
#endif
