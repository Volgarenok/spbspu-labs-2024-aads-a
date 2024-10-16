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

    List< T > & operator=(const List< T > & list);
    List< T > & operator=(List< T > && list);

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
  List< T > & List< T >::operator=(const List< T > & list)
  {
    List< T > temp(list);
    swap(temp);

    return *this;
  }

  template< typename T >
  List< T > & List< T >::operator=(List< T > && list)
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
    auto temp = new Node< T >(val);

    temp->next = head_;
    head_->prev = temp;
    head_ = head_->prev;

    size_++;
  }

  template< typename T >
  void List< T >::push_back(const T & val)
  {
   auto temp = new Node< T >(val);
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
    if (head_ == tail_)
    {
      return;
    }

    auto temp = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    delete temp;

    size_--;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    if (head_ == tail_)
    {
      return;
    }

    auto last = tail_->prev;
    if (last == head_)
    {
      head_ = head_->next;
      head_->prev = nullptr;
    }
    else
    {
      tail_->prev = last->prev;
      tail_->prev->next = tail_;
    }
    delete last;

    size_--;
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
