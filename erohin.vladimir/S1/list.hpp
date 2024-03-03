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
    List(std::initializer_list< T > init_list);
    template< class InputIt >
    List(InputIt first, InputIt last);
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
    void pop_front();
    void clear();
    void swap(List< T > & list);
    iterator insert_after(const_iterator pos, const T & value);
    iterator insert_after(const_iterator pos, T && value);
    iterator insert_after(const_iterator pos, size_t count, const T & value);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
  private:
    Node< T > * head_;
    Node< T > * before_head_;
    Node< T > * create_empty_node();
  };

  template< class T >
  Node< T > * List< T >::create_empty_node()
  {
    Node< T > * result = nullptr;
    try
    {
      result = new Node< T >(head_);
    }
    catch (const std::bad_alloc &)
    {
      clear();
      throw;
    }
    return before_head_;
  }

  template< class T >
  List< T >::List():
    head_(nullptr),
    before_head_(create_empty_node())
  {}

  template< class T >
  List< T >::List(const List< T > & list):
    head_(nullptr),
    before_head_(create_empty_node())
  {
    auto current_iter = list.begin();
    auto end_iter = list.end();
    while (current_iter != end_iter)
    {
      try
      {
        push_front(*(current_iter++));
      }
      catch (const std::bad_alloc &)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  List< T >::List(List< T > && list) noexcept:
    head_(list.head_),
    before_head_(list.before_head_)
  {
    list.head_ = nullptr;
    list.before_head_ = nullptr;
  }

  template< class T >
  List< T >::List(size_t count, const T & value):
    head_(nullptr),
    before_head_(new Node< T >(head_))
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
  List< T >::List(std::initializer_list< T > init_list):
    head_(nullptr),
    before_head_(nullptr)
  {
    auto init_begin = init_list.begin();
    auto init_end = init_list.end();
    while (init_begin != init_end)
    {
      try
      {
        push_front(*(--init_end));
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
    head_(nullptr),
    before_head_(new Node< T >(head_))
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
  }

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
    delete before_head_;
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
    Node< T > * new_node = new Node< T >(value, iter_result.node_->next_);
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
    ListIterator< T > iter_result(first.node_);
    ListIterator< T > iter_end(last.node_);
    while (iter_result != iter_end)
    {
      iter_result = erase_after(ListConstIterator< T >(iter_result.node_));
    }
    return iter_result;
  }
}

#endif
