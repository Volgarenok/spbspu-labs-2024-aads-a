#ifndef LIST_HPP
#define LIST_HPP

#include <list/node.hpp>
#include <list/iterator.hpp>
#include <list/constIterator.hpp>

namespace baranov
{
  template< class T >
  class List
  {
    public:
      List();
      List(const List & rhs);
      List(const List && rhs) noexcept;
      List(size_t count, const T & data);
      template < typename Iter >
      List(Iter begin, Iter end);
      ~List();
      T & back();
      const T & back() const;
      T & front();
      const T & front() const;
      Iterator< T > begin() noexcept;
      Iterator< T > end() noexcept;
      ConstIterator< T > cbegin() const noexcept;
      ConstIterator< T > cend() const noexcept;
      bool empty() const noexcept;
      size_t size() const noexcept;
      void push_back(const T & data);
      void pop_back();
      void push_front(const T & data);
      void pop_front();
      void assign(size_t count, const T & data);
      void clear();
      template < class UPredicate >
      void remove_if(UPredicate p);
      void remove(const T & data);
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
  List< T >::List(const List & rhs):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    Node< T > * current = rhs.head_;
    while (current)
    {
      try
      {
        push_back(current->data_);
        current = current->next_;
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  List< T >::List(const List && rhs) noexcept:
    head_(rhs.head_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.head_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = nullptr;
  }

  template< class T >
  List< T >::List(size_t count, const T & data):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    for (size_t i = 0; i < count; ++i)
    {
      try
      {
        push_front(data);
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  }

  template< class T >
  template< class Iter >
  List< T >::List(Iter begin, Iter end):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    for(; begin != end; ++begin)
    {
      try
      {
        push_back(*begin);
      }
      catch (...)
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
  T & List< T >::back()
  {
    return tail_->data_;
  }

  template< class T >
  const T & List< T >::back() const
  {
    return tail_->data_;
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
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template< class T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >();
  }

  template< class T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template< class T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return ConstIterator< T >();
  }

  template< class T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr || tail_ == nullptr;
  }

  template< class T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }

  template< class T >
  void List< T >::push_back(const T & data)
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
      topush->prev_ = tail_;
      tail_ = topush;
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
  void List< T >::push_front(const T & data)
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
      topush->next_ = head_;
      head_ = topush;
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
  void List< T >::assign(size_t count, const T & data)
  {
    List< T > newlist(count, data);
    swap(newlist);
  }

  template< class T >
  template < class UPredicate >
  void List< T >::remove_if(UPredicate p)
  {
    if (empty())
    {
      return;
    }
    auto i = begin();
    auto end = end();
    while (i != end)
    {
      if (p(*i))
      {
        Node< T > * todel = i;
        if (i->prev != nullptr)
        {
          i->prev_->next_=i->next_;
        }
        if (i->next_ != end)
        {
          i->next_->prev_ = i->prev_;
        }
        delete todel;
        ++i;
      }
    }
  }

  template< class T >
  void List< T >::remove(const T & data)
  {
    remove_if(
      [&](const T & other)
      {
        return other == data;
      }
    );
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

