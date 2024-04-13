#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace baranov
{
  template< class T >
  class List
  {
    public:
      List();
      List(const List &);
      ~List();
      Iterator< T > begin();
      Iterator< T > end();
      bool empty() const;
      size_t size();
      void push_back(T data);
      void pop_back();
      void push_front(T data);
      void pop_front();
      void clear();
      void swap(List &);
    private:
      Node< T > * head_;
      Node< T > * tail_;
      size_t size_;
  };


  template< class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< class T >
  List< T >::List(const List & other):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    Node< T > * current = other.head_;
    while (current)
    {
      push_back(current->data_);
      current = current->next_;
    }
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  Iterator< T > List< T >::begin()
  {
    return Iterator< T >(head_);
  }

  template< class T >
  Iterator< T > List< T >::end()
  {
    if (empty())
    {
      return begin();
    }
    if (tail_->next_ == nullptr)
    {
      Node< T > * imagNode = new Node< T >{ tail_->data_ };
      imagNode->prev_ = tail_;
      tail_->next_ = imagNode;
    }
    return tail_->next_;
  }

  template< class T >
  bool List< T >::empty() const
  {
    return head_ == nullptr || tail_ == nullptr;
  }

  template< class T >
  size_t List< T >::size()
  {
    return size_;
  }

  template< class T >
  void List< T >::push_back(T data)
  {
    Node< T > * topush = new Node< T >{ data };
    if (empty())
    {
      head_ = topush;
      tail_ = topush;
    }
    else
    {
      tail_->next_ = topush;
      tail_ = topush;
      tail_->prev_ = topush;
    }
    ++size_;
  }

  template< class T >
  void List< T >::pop_back()
  {
    assert(!empty());
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T > * newtail = tail_->prev_;
      delete tail_;
      tail_ = newtail;
      tail_->next_ = nullptr;
    }
    --size_;
  }

  template< class T >
  void List< T >::push_front(T data)
  {
    Node< T > * topush = new Node< T >{ data };
    if (empty())
    {
      head_ = topush;
      tail_ = topush;
    }
    else
    {
      head_->prev_ = topush;
      head_ = topush;
      head_->next_ = topush;
    }
    ++size_;
  }

  template< class T >
  void List< T >::pop_front()
  {
    assert(!empty());
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T > * newhead = head_->next_;
      delete head_;
      head_ = newhead;
      head_->prev_ = nullptr;
    }
    --size_;
  }

  template< class T >
  void List< T >::clear()
  {
    if (!empty())
    {
      while (head_)
      {
        Node< T > * temp = head_;
        head_ = head_->next_;
        delete temp;
      }
    }
  }

  template< class T >
  void List< T >::swap(List & rhs)
  {
    std::swap(rhs.head_, head_);
    std::swap(rhs.tail_, tail_);
    std::swap(rhs.size_, size_);
  }
}

#endif

