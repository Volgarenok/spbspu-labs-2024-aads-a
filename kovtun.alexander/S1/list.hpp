#ifndef LIST_HPP
#define LIST_HPP

#include <cassert>

#include "const_iterator.hpp"

namespace kovtun
{
  template< typename T >
  class List
  {
  public:
    List();
    ~List();
    List(const List< T > & list);
    List(List< T > && list) noexcept;

    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;

    bool empty() const noexcept;

    void push_front(const T & val);
    void push_back(const T & val);
    void pop_front();
    void pop_back();
    void clear();
    void swap(List< T > & list) noexcept;
    size_t size() const noexcept;

  private:
    Node< T > * head_;
    Node< T > * tail_;

    size_t size_;
  };

  template< typename T >
  List< T >::List()
  {
    tail_ = new Node< T >(nullptr, nullptr, T());
    head_ = tail_;
    size_ = 0;
  }

  template< typename T >
  List< T >::~List()
  {
   clear();
   delete tail_;
  }

  template< typename T >
  List< T >::List(const List< T > & list) :
    List()
  {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  List< T >::List(List< T > && list) noexcept :
    head_(list.head_),
    tail_(list.tail_),
    size_(list.size_)
  {
    list.head_ = nullptr;
    list.tail_ = nullptr;
    list.size_ = 0;
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >(tail_);
  }

  template< typename T >
  void List< T >::push_front(const T & val)
  {

  }

  template< typename T >
  void List< T >::push_back(const T & val)
  {
   // TODO: first
   auto temp = new Node< T >(nullptr, nullptr, val);
   if (head_ == tail_)
   {
      temp->next = tail_;
      head_ = temp;
      tail_->prev = head_;
   }
   else
   {
     auto last = tail_->prev;
     last->next = temp;

     temp->prev = last;
     temp->next = tail_;
     tail_->prev = temp;
   }

   size_++;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    // TODO: first
    if (head_ == tail_)
    {
      return;
    }

    auto temp = head_;
    head_ = head_->next;
    delete temp;

    size_--;
  }

  template< typename T >
  void List< T >::pop_back()
  {

  }

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void List< T >::swap(List< T > & list) noexcept
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
  }

  template< typename T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }
}

#endif
