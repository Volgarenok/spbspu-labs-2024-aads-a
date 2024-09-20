#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <utility>
#include "list_const_iterator.hpp"
#include "list_iterator.hpp"
#include "list_node.hpp"

namespace lebedev
{
  template< class T >
  class List
  {
  public:
    using iterator = ListIterator< T >;
    using const_iterator = ConstListIterator< T >;

    List();
    List(const List< T > & list);
    List(List< T > && list) noexcept;
    explicit List(size_t n);
    List(size_t n, const T & val);
    ~List();

    List< T > & operator=(const List< T > & list);
    List< T > & operator=(List< T > && list) noexcept;

    void push_back(const T & val);
    void push_back(T && val);
    void push_front(const T & val);
    void push_front(T && val);

    void pop_back();
    void pop_front();

    bool empty() const noexcept;
    void clear() noexcept;
    void swap(List< T > & list);
    size_t capacity() const noexcept;

    T & front();
    T & back();
    const T & front() const;
    const T & back() const;

    void assign(size_t n, const T & val);

    void remove(const T & val);
    template< class Predicate >
    void remove_if(Predicate pred);

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

  private:
    detail::Node< T > * head_;
    detail::Node< T > * tail_;
    size_t size_;
    detail::Node< T > * remove_node(detail::Node< T > * node);
  };

  template< class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}
  template< class T >
  List< T >::List(const List< T > & list):
    List()
  {
    if (!list.empty())
    {
      detail::Node< T > * node = list.head_;
      while (node)
      {
        push_back(node->data_);
        node = node->next_;
      }
    }
  }
  template< class T >
  List< T >::List(List< T > && list) noexcept:
    head_(list.head_),
    tail_(list.tail_),
    size_(list.size_)
  {
    list.head_ = nullptr;
    list.tail_ = nullptr;
    list.size_ = 0;
  }
  template< class T >
  List< T >::List(size_t n):
    List(n, T())
  {}
  template< class T >
  List< T >::List(size_t n, const T & val):
    List()
  {
    assign(n, val);
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  List< T > & List< T >::operator=(const List< T > & list)
  {
    if (head_ != list.head_)
    {
      List< T > temp(list);
      swap(temp);
    }
    return *this;
  }
  template< class T >
  List< T > & List< T >::operator=(List< T > && list) noexcept
  {
    if (head_ != list.head_)
    {
      clear();
      head_ = list.head_;
      tail_ = list.tail_;
      size_ = list.size_;
      list.head_ = nullptr;
      list.tail_ = nullptr;
      list.size_ = 0;
    }
    return *this;
  }

  template< class T >
  void List< T >::push_back(const T & val)
  {
    detail::Node< T > * node = new detail::Node< T >(val, nullptr, tail_);
    if ((head_ == nullptr) && (tail_ == nullptr))
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      node->prev_ = tail_;
      tail_->next_ = node;
      tail_ = node;
    }
    ++size_;
  }
  template< class T >
  void List< T >::push_back(T && val)
  {
    detail::Node< T > * node = new detail::Node< T >(std::move(val), nullptr, tail_);
    if ((head_ == nullptr) && (tail_ == nullptr))
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      node->prev_ = tail_;
      tail_->next_ = node;
      tail_ = node;
    }
    ++size_;
  }
  template< class T >
  void List< T >::push_front(const T & val)
  {
    detail::Node< T > * node = new detail::Node< T >(val, head_, nullptr);
    if ((head_ == nullptr) && (tail_ == nullptr))
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      node->next_ = head_;
      head_->prev_ = node;
      head_ = node;
    }
    ++size_;
  }
  template< class T >
  void List< T >::push_front(T && val)
  {
    detail::Node< T > * node = new detail::Node< T >(std::move(val), head_, nullptr);
    if ((head_ == nullptr) && (tail_ == nullptr))
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      node->next_ = head_;
      head_->prev_ = node;
      head_ = node;
    }
    ++size_;
  }

  template< class T >
  void List< T >::pop_back()
  {
    if (tail_ == nullptr)
    {
      return;
    }
    detail::Node< T > * newtail = tail_->prev_;
    if (newtail)
    {
      newtail->next_ = nullptr;
    }
    else
    {
      head_ = nullptr;
    }
    delete tail_;
    tail_ = newtail;
    --size_;
  }
  template< class T >
  void List< T >::pop_front()
  {
    if (head_ == nullptr)
    {
      return;
    }
    detail::Node< T > * newhead = head_->next_;
    if (newhead)
    {
      newhead->prev_ = nullptr;
    }
    else
    {
      tail_ = nullptr;
    }
    delete head_;
    head_ = newhead;
    --size_;
  }

  template< class T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }
  template< class T >
  void List< T >::clear() noexcept
  {
    while (tail_)
    {
      pop_back();
    }
  }
  template< class T >
  void List< T >::swap(List< T > & list)
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
  }
  template< class T >
  size_t List< T >::capacity() const noexcept
  {
    return size_;
  }

  template< class T >
  T & List< T >::front()
  {
    return head_->data_;
  }
  template< class T >
  T & List< T >::back()
  {
    return tail_->data_;
  }
  template< class T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }
  template< class T >
  const T & List< T >::back() const
  {
    return tail_->data_;
  }

  template< class T >
  void List< T >::assign(size_t n, const T & val)
  {
    List< T > new_list;
    for (size_t i = 0; i < n; i++)
    {
      new_list.push_back(val);
    }
    this->swap(new_list);
  }

  template< class T >
  void List< T >::remove(const T & val)
  {
    detail::Node< T > * node = head_;
    while (node)
    {
      if (node->data_ == val)
      {
        node = remove_node(node);
      }
      else
      {
        node = node->next_;
      }
    }
  }
  template< class T >
  template< class Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    detail::Node< T > * node = head_;
    while (node)
    {
      if (pred(node->data_))
      {
        node = remove_node(node);
      }
      else
      {
        node = node->next_;
      }
    }
  }

  template< class T >
  detail::Node< T > * List< T >::remove_node(detail::Node< T > * node)
  {
    detail::Node< T > * prev_node = node->prev_;
    detail::Node< T > * next_node = node->next_;
    if (node == head_)
    {
      pop_front();
      node = next_node;
    }
    else if (node == tail_)
    {
      pop_back();
      node = prev_node;
    }
    else
    {
      prev_node->next_ = next_node;
      next_node->prev_ = prev_node;
      delete node;
      node = prev_node;
      size_--;
    }
    return node;
  }

  template< class T >
  ListIterator< T > List< T >::begin() noexcept
  {
    return iterator(head_);
  }
  template< class T >
  ListIterator< T > List< T >::end() noexcept
  {
    return iterator(tail_->next_);
  }
  template< class T >
  ConstListIterator< T > List< T >::begin() const noexcept
  {
    return const_iterator(head_);
  }
  template< class T >
  ConstListIterator< T > List< T >::end() const noexcept
  {
    return const_iterator(tail_->next_);
  }
  template< class T >
  ConstListIterator< T > List< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }
  template< class T >
  ConstListIterator< T > List< T >::cend() const noexcept
  {
    return const_iterator(tail_->next_);
  }
}

#endif
