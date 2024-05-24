#ifndef LIST_HPP
#define LIST_HPP

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
    List & operator=(const List & rhs);
    List & operator=(List && rhs) noexcept;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    T & front();
    const T & front() const;
    bool empty() const noexcept;
    void push_front(const T & value);
    void push_front(T && value) noexcept;
    void pop_front();
    void clear() noexcept;
    void swap(List< T > & list) noexcept;
    iterator insert_after(const_iterator pos, const T & value);
    iterator insert_after(const_iterator pos, T && value) noexcept;
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
    void splice_after(const_iterator pos, List< T > && other) noexcept;
    void splice_after(const_iterator pos, List< T > & other, const_iterator it);
    void splice_after(const_iterator pos, List< T > && other, const_iterator it) noexcept;
    void splice_after(const_iterator pos, List< T > & other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, List< T > && other, const_iterator first, const_iterator last) noexcept;
    void reverse() noexcept;
    template< class Compare >
    void sort(Compare cmp);
    void sort();
  private:
    detail::Node< T > * head_;
  };

  template< class T >
  List< T >::List():
    head_(nullptr)
  {}

  template< class T >
  List< T >::List(const List< T > & list):
    List(list.cbegin(), list.cend())
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
      catch (...)
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
    while (first != last)
    {
      try
      {
        push_front(*(first++));
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    reverse();
  }

  template< class T >
  List< T >::List(std::initializer_list< T > init_list):
    List(init_list.begin(), init_list.end())
  {}

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  List< T > & List< T >::operator=(const List< T > & rhs)
  {
    if (this != std::addressof(rhs))
    {
      List< T > temp(rhs);
      swap(temp);
    }
    return *this;
  }

  template< class T >
  List< T > & List< T >::operator=(List< T > && rhs) noexcept
  {
    if (this != std::addressof(rhs))
    {
      List< T > temp(std::move(rhs));
      swap(temp);
    }
    return *this;
  }

  template< class T >
  ListIterator< T > List< T >::begin()
  {
    return iterator(head_);
  }

  template< class T >
  ListIterator< T > List< T >::end()
  {
    return iterator(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::begin() const
  {
    return const_iterator(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::end() const
  {
    return const_iterator(nullptr);
  }

  template< class T >
  ListConstIterator< T > List< T >::cbegin() const
  {
    return const_iterator(head_);
  }

  template< class T >
  ListConstIterator< T > List< T >::cend() const
  {
    return const_iterator(nullptr);
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
  bool List< T >::empty() const noexcept
  {
    return !head_;
  }

  template< class T >
  void List< T >::push_front(const T & value)
  {
    push_front(T(value));
  }

  template< class T >
  void List< T >::push_front(T && value) noexcept
  {
    detail::Node< T > * elem = new detail::Node< T >(std::move(value), head_);
    head_ = elem;
  }

  template< class T >
  void List< T >::pop_front()
  {
    detail::Node< T > * new_head = head_->next_;
    delete head_;
    head_ = new_head;
  }

  template< class T >
  void List< T >::clear() noexcept
  {
    while (head_)
    {
      pop_front();
    }
  }

  template< class T >
  void List< T >::swap(List< T > & list) noexcept
  {
    std::swap(head_, list.head_);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(const_iterator pos, const T & value)
  {
    return insert_after(pos, T(value));
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(const_iterator pos, T && value) noexcept
  {
    iterator iter_result(const_cast< detail::Node< T > * >(pos.node_));
    detail::Node< T > * new_node = new detail::Node< T >(std::move(value), iter_result.node_->next_);
    iter_result.node_->next_ = new_node;
    return (++iter_result);
  }

  template< class T >
  ListIterator< T > List< T >::insert_after(const_iterator pos, size_t count, const T & value)
  {
    if (count == 0)
    {
      return iterator(pos.node_);
    }
    List< T > temp;
    for (size_t i = 0; i < count; ++i)
    {
      temp.push_front(value);
    }
    push_front(temp.front());
    temp.pop_front();
    splice_after(cbegin(), std::move(temp));
    return iterator(pos.node_);
  }

  template< class T >
  ListIterator< T > List< T >::erase_after(const_iterator pos)
  {
    iterator iter_result(const_cast< detail::Node< T > * >(pos.node_));
    detail::Node< T > * to_delete = iter_result.node_->next_;
    detail::Node< T > * to_become_next = to_delete->next_;
    delete to_delete;
    iter_result.node_->next_ = to_become_next;
    return iterator(to_become_next);
  }

  template< class T >
  ListIterator< T > List< T >::erase_after(const_iterator first, const_iterator last)
  {
    while (std::next(first) != last)
    {
      erase_after(first);
    }
    return iterator(const_cast< detail::Node< T > * >(last.node_));
  }

  template< class T >
  void List< T >::remove(const T & value)
  {
    remove_if(
      [&](const T & elem)
      {
        return (elem == value);
      }
    );
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
    while (std::next(iter_begin) != iter_end)
    {
      if (p(*std::next(iter_begin)))
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
    if (count == 0)
    {
      return;
    }
    List< T > temp;
    temp.push_front(value);
    temp.insert_after(cbegin(), count - 1, value);
    assign(temp.begin(), temp.end());
  }

  template< class T >
  template< class InputIt >
  void List< T >::assign(InputIt first, InputIt last)
  {
    List< T > temp;
    while (first != last)
    {
      temp.push_front(*(first++));
    }
    temp.reverse();
    clear();
    push_front(std::move(temp.front()));
    temp.pop_front();
    splice_after(cbegin(), std::move(temp));
  }

  template< class T >
  void List< T >::assign(std::initializer_list< T > init_list)
  {
    assign(init_list.begin(), init_list.end());
  }

  template< class T >
  void List< T >::splice_after(const_iterator pos, List< T > & other)
  {
    splice_after(pos, List< T >(other));
  }

  template< class T >
  void List< T >::splice_after(const_iterator pos, List< T > && other) noexcept
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
  void List< T >::splice_after(const_iterator pos, List< T > & other, const_iterator it)
  {
    splice_after(pos, List< T >(other), it);
  }

  template< class T >
  void List< T >::splice_after(const_iterator pos, List< T > && other, const_iterator it) noexcept
  {
    if (pos == it || pos == std::next(it))
    {
      return;
    }
    splice_after(pos, std::move(other), it, other.cend());
  }

  template< class T >
  void List< T >::splice_after(const_iterator pos, List< T > & other, const_iterator first, const_iterator last)
  {
    splice_after(pos, T(other), first, last);
  }

  template< class T >
  void List< T >::splice_after(const_iterator pos, List< T > && other, const_iterator first, const_iterator last) noexcept
  {
    auto iter_current = first;
    auto iter_end = last;
    while (std::next(iter_current) != iter_end)
    {
      insert_after(pos, std::move(*std::next(iter_current)));
      other.erase_after(iter_current);
      ++pos;
    }
  }

  template< class T >
  void List< T >::reverse() noexcept
  {
    if (empty())
    {
      return;
    }
    const_iterator iter_begin = cbegin();
    const_iterator iter_end = cend();
    const_iterator iter_current = iter_begin;
    ++iter_current;
    while (iter_current != iter_end)
    {
      push_front(std::move(iter_current.node_->data_));
      ++iter_current;
    }
    erase_after(iter_begin, iter_end);
  }

  template< class T >
  template< class Compare >
  void List< T >::sort(Compare cmp)
  {
    if (empty())
    {
      return;
    }
    bool is_sorted = false;
    while (!is_sorted)
    {
      is_sorted = true;
      auto iter = begin();
      while (std::next(iter) != end())
      {
        if (!cmp(*iter, *std::next(iter)))
        {
          std::swap(*iter, *std::next(iter));
          is_sorted = false;
        }
        ++iter;
      }
    }
  }

  template< class T >
  void List< T >::sort()
  {
    sort(std::less< T >{});
  }

  namespace detail
  {
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
  }

  template< class T >
  bool operator==(const List< T > & lhs, const List< T > & rhs)
  {
    return (detail::compare(lhs, rhs) == 0);
  }

  template< class T >
  bool operator!=(const List< T > & lhs, const List< T > & rhs)
  {
    return !(lhs == rhs);
  }

  template< class T >
  bool operator<(const List< T > & lhs, const List< T > & rhs)
  {
    return (detail::compare(lhs, rhs) < 0);
  }

  template< class T >
  bool operator<=(const List< T > & lhs, const List< T > & rhs)
  {
    return (detail::compare(lhs, rhs) <= 0);
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
