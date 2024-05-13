#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>
#include <utility>
#include "node.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"

namespace petuhov
{
  template < typename T >
  class List
  {
  public:
    List();
    List(const List< T > &other);
    List(List< T > &&other) noexcept;
    ~List();
    
    Iterator< T > begin() noexcept;
    Iterator< T > end() noexcept;
    ConstIterator< T > cbegin() const noexcept;
    ConstIterator< T > cend() const noexcept;
    
    T &front();
    const T &front() const;
    bool empty() const noexcept;
    void push_front(const T &value);
    void pop_front();
    void clear() noexcept;
    void swap(List &other) noexcept;

    List(size_t size, const T &value);
    void assign(size_t count, const T &value);
    void remove(const T &value);
    template < typename Predicate >
    void remove_if(Predicate pred);

    List(std::initializer_list< T > ilist);
    template < typename InputIterator >
    List(InputIterator first, InputIterator last);
    Iterator< T > insert(Iterator< T > pos, const T &value);
    Iterator< T > erase(Iterator< T > pos);
    template < typename InputIterator >
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list< T > ilist);
    void splice(Iterator< T > pos, List< T > &other);
    void reverse() noexcept;

    List< T >& operator=(const List< T > &other);
    List< T >& operator=(List< T >&& other) noexcept;
    List< T >& operator=(std::initializer_list< T > ilist);

  private:
    detail::Node< T > *head_;
    detail::Node< T > *tail_;
  };

  template < typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  List< T >::List(const List< T > &other): head_(nullptr), tail_(nullptr)
  {
    detail::Node< T > *current = other.head_;
    while (current)
    {
      push_front(current->value_);
      current = current->next_;
    }
    reverse();
  }

  template < typename T >
  List< T >::List(List< T > &&other) noexcept : head_(other.head_), tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template < typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template < typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(nullptr);
  }

  template < typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template < typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return ConstIterator< T >(nullptr);
  }

  template < typename T >
  T &List< T >::front()
  {
    return head_->value_;
  }

  template < typename T >
  const T &List< T >::front() const
  {
    return head_->value_;
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template < typename T >
  void List< T >::push_front(const T &value)
  {
    detail::Node< T > *newNode = new detail::Node< T >{value, head_};
    head_ = newNode;
    if (tail_ == nullptr)
    {
      tail_ = head_;
    }
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (head_)
    {
      detail::Node< T > *temp = head_;
      head_ = head_->next_;
      delete temp;
      if (head_ == nullptr)
      {
        tail_ = nullptr;
      }
    }
  }

  template < typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void List< T >::swap(List &other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template < typename T >
  void List< T >::reverse() noexcept
  {
    detail::Node< T > *prev = nullptr, *current = head_, *next = nullptr;
    tail_ = head_;
    while (current)
    {
      next = current->next_;
      current->next_ = prev;
      prev = current;
      current = next;
    }
    head_ = prev;
  }

  template < typename T >
  List< T >::List(size_t count, const T &value): 
    head_(nullptr),
    tail_(nullptr)
  {
    detail::Node< T > *lastNode = nullptr;
    for (size_t i = 0; i < count; ++i)
    {
      detail::Node< T > *newNode = new detail::Node< T >(value);
      if (!head_)
      {
        head_ = newNode;
      }
      else
      {
        lastNode->next_ = newNode;
      }
      lastNode = newNode;
    }
    tail_ = lastNode;
  }

  template < typename T >
  void List< T >::assign(size_t count, const T &value)
  {
    clear();
    detail::Node< T > *lastNode = nullptr;
    for (size_t i = 0; i < count; ++i)
    {
      detail::Node< T > *newNode = new detail::Node< T >(value);
      if (!head_)
      {
        head_ = newNode;
      }
      else
      {
        lastNode->next_ = newNode;
      }
      lastNode = newNode;
    }
    tail_ = lastNode;
  }

  template < typename T >
  void List< T >::remove(const T &value)
  {
    detail::Node< T > *current = head_;
    detail::Node< T > *prev = nullptr;
    while (current)
    {
      if (current->value_ == value)
      {
        detail::Node< T > *toDelete = current;
        current = current->next_;
        if (prev)
        {
          prev->next_ = current;
        }
        else
        {
          head_ = current;
        }
        if (!current)
        {
          tail_ = prev;
        }
        delete toDelete;
      }
      else
      {
        prev = current;
        current = current->next_;
      }
    }
  }

  template < typename T >
  template < typename Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    detail::Node< T > *current = head_;
    detail::Node< T > *prev = nullptr;
    while (current)
    {
      if (pred(current->value_))
      {
        detail::Node< T > *toDelete = current;
        current = current->next_;
        if (prev)
        {
          prev->next_ = current;
        }
        else
        {
          head_ = current;
        }
        if (!current)
        {
          tail_ = prev;
        }
        delete toDelete;
      }
      else
      {
        prev = current;
        current = current->next_;
      }
    }
  }

  template < typename T >
  List< T >::List(std::initializer_list< T > ilist):
    head_(nullptr),
    tail_(nullptr)
  {
    for (const T &item : ilist)
    {
      detail::Node< T > *newNode = new detail::Node< T >(item);
      if (!tail_)
      {
        head_ = tail_ = newNode;
      }
      else
      {
        tail_->next_ = newNode;
        tail_ = newNode;
      }
    }
  }

  template < typename T >
  template < typename InputIterator >
  List< T >::List(InputIterator first, InputIterator last):
    head_(nullptr),
    tail_(nullptr)
  {
    for (; first != last; ++first)
    {
      detail::Node< T > *newNode = new detail::Node< T >(*first);
      if (!tail_)
      {
        head_ = tail_ = newNode;
      }
      else
      {
        tail_->next_ = newNode;
        tail_ = newNode;
      }
    }
  }

  template < typename T >
  Iterator< T > List< T >::insert(Iterator< T > pos, const T &value)
  {
    detail::Node< T > *newNode = new detail::Node< T >(value);
    if (pos.node_ == head_)
    {
      newNode->next_ = head_;
      head_ = newNode;
      if (!tail_)
        tail_ = newNode;
    }
    else
    {
      detail::Node< T > *current = head_;
      while (current && current->next_ != pos.node_)
      {
        current = current->next_;
      }
      newNode->next_ = current->next_;
      current->next_ = newNode;
      if (newNode->next_ == nullptr)
        tail_ = newNode;
    }
    return Iterator< T >(newNode);
  }

  template < typename T >
  Iterator< T > List< T >::erase(Iterator< T > pos)
  {
    if (!head_ || !pos.node_)
      return Iterator< T >(nullptr);
    detail::Node< T > *toDelete = pos.node_;
    if (toDelete == head_)
    {
      head_ = head_->next_;
      if (head_ == nullptr)
        tail_ = nullptr;
    }
    else
    {
      detail::Node< T > *prev = head_;
      while (prev && prev->next_ != toDelete)
      {
        prev = prev->next_;
      }
      if (prev)
      {
        prev->next_ = toDelete->next_;
        if (prev->next_ == nullptr)
          tail_ = prev;
      }
    }
    delete toDelete;
    return Iterator< T >(toDelete->next_);
  }

  template < typename T >
  template < typename InputIterator >
  void List< T >::assign(InputIterator first, InputIterator last)
  {
    clear();
    for (; first != last; ++first)
    {
      detail::Node< T > *newNode = new detail::Node< T >(*first);
      if (!tail_)
      {
        head_ = tail_ = newNode;
      }
      else
      {
        tail_->next_ = newNode;
        tail_ = newNode;
      }
    }
  }

  template < typename T >
  void List< T >::assign(std::initializer_list< T > ilist)
  {
    assign(ilist.begin(), ilist.end());
  }

  template < typename T >
  List< T > &List< T >::operator=(const List< T > &other)
  {
    if (this != &other)
    {
      List< T > temp(other);
      swap(temp);
    }
    return *this;
  }

  template < typename T >
  List< T > &List< T >::operator=(List< T > &&other) noexcept
  {
    if (this != &other)
    {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      other.head_ = other.tail_ = nullptr;
    }
    return *this;
  }

  template < typename T >
  List< T > &List< T >::operator=(std::initializer_list< T > ilist)
  {
    clear();
    detail::Node< T > *lastNode = nullptr;
    for (const T &item : ilist)
    {
      detail::Node< T > *newNode = new detail::Node< T >(item);
      if (!head_)
      {
        head_ = newNode;
      }
      else
      {
        lastNode->next_ = newNode;
      }
      lastNode = newNode;
    }
    tail_ = lastNode;
    return *this;
  }
}

#endif
