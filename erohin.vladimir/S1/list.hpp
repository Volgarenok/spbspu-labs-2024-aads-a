#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

#include <initializer_list>
#include <stdexcept>
#include "node.hpp"
#include "list_iterator.hpp"
#include "list_const_iterator.hpp"

namespace erohin
{
  template< class T >
  class List
  {
  public:
    using iterator = ListIterator< T >;
    using const_iterator = ListConstIterator< T >;
    List();
    List(const List & list);
    List(List && list) noexcept;
    List(size_t count, const T & value);
    template< class InputIt >
    List(InputIt first, InputIt last);
    List(std::initializer_list< T > init_list);
    ~List();
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    T & front();
    const T & front() const;
    bool empty() const;
    void push_front(const T & value);
    void push_front(T && value);
    void pop_front();
    void clear();
    void swap(List< T > & list);
    iterator insert_after(const_iterator pos, const T & value);
    iterator insert_after(const_iterator pos, T && value);
    iterator insert_after(const_iterator pos, size_t count, const T & value);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void remove(const T & value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void assign(size_t count, const T & value);
    template< class InputIt >
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list< T > init_list);
    void splice_after(const_iterator pos, List< T > & other);
    void splice_after(const_iterator pos, List< T > && other);
    void splice_after(const_iterator pos, List< T > & other, const_iterator it);
    void splice_after(const_iterator pos, List< T > && other, const_iterator it);
    void splice_after(const_iterator pos, List< T > & other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, List< T > && other, const_iterator first, const_iterator last);
    void reverse();
  private:
    Node< T > * head_;
  };

  template< class T >
  List< T >::List():
    head_(nullptr)
  {}

  template< class T >
  List< T >::List(const List< T > & list): List(list.cbegin(), list.cend())
  {}

  template< class T >
  List< T >::List(List< T > && list) noexcept:
    head_(list.head_)
  {
    list.head_ = nullptr;
  }

  template< class T >
  List< T >::List(size_t count, const T & value):
    head_(nullptr)
  {
    for (size_t i = 0; i < count; ++i)
    {
      try
      {
        push_front(value);
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  template< class InputIt >
  List< T >::List(InputIt first, InputIt last):
    head_(nullptr)
  {
    while(first != last)
    {
      try
      {
        push_front(*(first++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
    reverse();
  }

  template< class T >
  List< T >::List(std::initializer_list< T > init_list): List(init_list.begin(), init_list.end())
  {}

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(head_);
  }

  template< class T >
  ListIterator< T > List< T >::end()
  {
    return ListIterator< T >(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::begin() const
  {
    return ListConstIterator< T >(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::end() const
  {
    return ListConstIterator< T >(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::cbegin() const
  {
    return ListConstIterator< T >(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::cend() const
  {
    return ListConstIterator< T >(nullptr);
  }

  template< class T >
  T & List< T >::front()
  {
    return head_->data_;
  }

  template< class T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }

  template< class T >
  bool List< T >::empty() const
  {
    return !head_;
  }

  template< class T >
  void List< T >::push_front(const T & value)
  {
    Node< T > * elem = new Node< T >(value, head_);
    head_ = elem;
  }

  template< class T >
  void List< T >::push_front(T && value)
  {
    Node< T > * elem = new Node< T >(std::move(value), head_);
    head_ = elem;
  }

  template< class T >
  void List< T >::pop_front()
  {
    Node< T > * new_head = head_->next_;
    delete head_;
    head_ = new_head;
  }

  template< class T >
  void List< T >::clear()
  {
    while (head_)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::swap(List< T > & list)
  {
    std::swap(head_, list.head_);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(ListConstIterator< T > pos, const T & value)
  {
    ListIterator< T > iter_result(pos.node_);
    Node< T > * new_node = new Node< T >(value, iter_result.node_->next_);
    iter_result.node_->next_ = new_node;
    return (++iter_result);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(ListConstIterator< T > pos, T && value)
  {
    ListIterator< T > iter_result(pos.node_);
    Node< T > * new_node = new Node< T >(std::move(value), iter_result.node_->next_);
    iter_result.node_->next_ = new_node;
    return (++iter_result);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(ListConstIterator< T > pos, size_t count, const T & value)
  {
    for (size_t i = 0; i < count; ++i)
    {
      pos = insert_after(pos, value);
    }
    return pos;
  }

  template< class T >
  ListIterator< T > List< T >::erase_after(ListConstIterator< T > pos)
  {
    ListIterator< T > iter_result(pos.node_);
    Node< T > * to_delete = iter_result.node_->next_;
    Node< T > * to_become_next = to_delete->next_;
    delete to_delete;
    iter_result.node_->next_ = to_become_next;
    return ListIterator< T >(to_become_next);
  }

  template< class T >
  ListIterator< T > List< T >::erase_after(ListConstIterator< T > first, ListConstIterator< T > last)
  {
    while (first + 1 != last)
    {
      erase_after(first);
    }
    return ListIterator< T >(last.node_);
  }

  template< class T >
  void List< T >::remove(const T & value)
  {
    remove_if([&](T elem){ return (elem == value); });
  }

  template< class T >
  template< class UnaryPredicate >
  void List< T >::remove_if(UnaryPredicate p)
  {
    if (empty())
    {
      return;
    }
    bool is_front_equal_value = p(front());
    auto iter_begin = cbegin();
    auto iter_end = cend();
    while (iter_begin + 1 != iter_end)
    {
      if (p(*(iter_begin + 1)))
      {
        erase_after(iter_begin);
      }
      else
      {
        ++iter_begin;
      }
    }
    if (is_front_equal_value)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::assign(size_t count, const T & value)
  {
    clear();
    for (size_t i = 0; i < count; ++i)
    {
      push_front(value);
    }
  }

  template< class T >
  template< class InputIt >
  void List< T >::assign(InputIt first, InputIt last)
  {
    clear();
    while(first != last)
    {
      try
      {
        push_front(*(first++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
    reverse();
  }

  template< class T >
  void List< T >::assign(std::initializer_list< T > init_list)
  {
    assign(init_list.begin(), init_list.end());
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > & other)
  {
    auto iter_current = other.cbegin();
    auto iter_end = other.cend();
    while (iter_current != iter_end)
    {
      insert_after(pos, std::move(*iter_current));
      ++iter_current;
      ++pos;
    }
    other.clear();
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > && other)
  {
    auto iter_current = other.cbegin();
    auto iter_end = other.cend();
    while (iter_current != iter_end)
    {
      insert_after(pos, std::move(*iter_current));
      ++iter_current;
      ++pos;
    }
    other.clear();
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > & other, ListConstIterator< T > it)
  {
    if (pos == it || pos == (it + 1))
    {
      return;
    }
    splice_after(pos, other, it, other.cend());
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > && other, ListConstIterator< T > it)
  {
    if (pos == it || pos == (it + 1))
    {
      return;
    }
    splice_after(pos, std::move(other), it, other.cend());
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > & other, ListConstIterator< T > first, ListConstIterator< T > last)
  {
    auto iter_current = first;
    auto iter_end = last;
    while (iter_current + 1 != iter_end)
    {
      insert_after(pos, std::move(*(iter_current + 1)));
      other.erase_after(iter_current);
      ++pos;
    }
  }

  template< class T >
  void List< T >::splice_after(ListConstIterator< T > pos, List< T > && other, ListConstIterator< T > first, ListConstIterator< T > last)
  {
    auto iter_current = first;
    auto iter_end = last;
    while (iter_current + 1 != iter_end)
    {
      insert_after(pos, std::move(*(iter_current + 1)));
      other.erase_after(iter_current);
      ++pos;
    }
  }

  template< class T >
  void List< T >::reverse()
  {
    if (empty())
    {
      return;
    }
    ListConstIterator< T > iter_begin = cbegin();
    ListConstIterator< T > iter_end = cend();
    ListConstIterator< T > iter_current = iter_begin;
    ++iter_current;
    while(iter_current != iter_end)
    {
      push_front(std::move(iter_current.node_->data_));
      ++iter_current;
    }
    erase_after(iter_begin, iter_end);
  }

  template< class T >
  int compare(const List< T > & lhs, const List< T > & rhs)
  {
    auto lbegin = lhs.cbegin();
    auto lend = lhs.cend();
    auto rbegin = rhs.cbegin();
    auto rend = rhs.cend();
    bool is_rhs_end_earlier = false;
    bool is_lhs_end_earlier = false;
    bool is_lhs_less = false;
    bool is_unequal_found = false;
    while (lbegin != lend || rbegin != rend)
    {
      is_lhs_end_earlier = (lbegin == lend) && (rbegin != rend);
      is_rhs_end_earlier = (lbegin != lend) && (rbegin == rend);
      if (is_lhs_end_earlier && !is_rhs_end_earlier)
      {
        return -1;
      }
      else if (!is_lhs_end_earlier && is_rhs_end_earlier)
      {
        return 1;
      }
      else if (*lbegin != *rbegin && !is_unequal_found)
      {
        is_lhs_less = (*lbegin < *rbegin);
        is_unequal_found = true;
      }
      ++lbegin;
      ++rbegin;
    }
    return (!is_unequal_found) ? 0 : (1 - 2 * is_lhs_less);
  }

  template< class T >
  bool operator==(const List< T > & lhs, const List< T > & rhs)
  {
    return (compare(lhs, rhs) == 0);
  }

  template< class T >
  bool operator!=(const List< T > & lhs, const List< T > & rhs)
  {
    return !(lhs == rhs);
  }

  template< class T >
  bool operator<(const List< T > & lhs, const List< T > & rhs)
  {
    return (compare(lhs, rhs) < 0);
  }

  template< class T >
  bool operator<=(const List< T > & lhs, const List< T > & rhs)
  {
    return (compare(lhs, rhs) <= 0);
  }

  template< class T >
  bool operator>(const List< T > & lhs, const List< T > & rhs)
  {
    return !(lhs <= rhs);
  }

  template< class T >
  bool operator>=(const List< T > & lhs, const List< T > & rhs)
  {
    return !(lhs < rhs);
  }
}

#endif
