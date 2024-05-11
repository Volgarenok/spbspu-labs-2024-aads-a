#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <utility>
#include "const_list_iterator.hpp"
#include "list_iterator.hpp"
#include "node.hpp"

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
    //List(List< T > && list);
    ~List();

    //List< T > & operator=(const List< T > & list);
    //List< T > & operator=(List< T > && list);

    void push_back(const T & val);
    void push_back(T && val);
    void push_front(const T & val);
    void push_front(T && val);

    void pop_back();
    void pop_front();

    bool empty() const noexcept;
    void clear() noexcept;
    void swap(List< T > & list);

    T & front();
    T & back();
    const T & front() const;
    const T & back() const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    /////////////////////////////////
    void outputList(std::ostream & out) const
    {
      detail::Node< T > * head = head_;
      while (head)
      {
        out << head->data_ << '\n';
        head = head->next_;
      }
    }
    ///////////////////////////////////

  private:
    detail::Node< T > * head_;
    detail::Node< T > * tail_;
  };

  template<class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}
  template<class T >
  List< T >::List(const List< T > & list):
    List()
  {
    if (!list.empty())
    {
      const_iterator iter = list.cbegin();
      const_iterator end = list.cend();
      while (iter != end)
      {
        push_back(*iter);
        iter++;
      }
      push_back(*iter);
    }
  }

  template<class T >
  List< T >::~List()
  {
    clear();
  }

  template<class T >
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
  }
  template<class T >
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
  }
  template<class T >
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
  }
  template<class T >
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
  }

  template<class T >
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
  }
  template<class T >
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
  }

  template<class T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }
  template<class T >
  void List< T >::clear() noexcept
  {
    while (tail_)
    {
      pop_back();
    }
  }
  template<class T >
  void List< T >::swap(List< T > & list)
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
  }

  template<class T >
  T & List< T >::front()
  {
    return head_->data_;
  }
  template<class T >
  T & List< T >::back()
  {
    return tail_->data_;
  }
  template<class T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }
  template<class T >
  const T & List< T >::back() const
  {
    return tail_->data_;
  }

  template< class T >
  ListIterator< T > List< T >::begin() noexcept
  {
    return iterator(head_);
  }
  template< class T >
  ListIterator< T > List< T >::end() noexcept
  {
    return iterator(tail_);
  }
  template< class T >
  ConstListIterator< T > List< T >::begin() const noexcept
  {
    return const_iterator(head_);
  }
  template< class T >
  ConstListIterator< T > List< T >::end() const noexcept
  {
    return const_iterator(tail_);
  }
  template< class T >
  ConstListIterator< T > List< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }
  template< class T >
  ConstListIterator< T > List< T >::cend() const noexcept
  {
    return const_iterator(tail_);
  }
}

#endif
