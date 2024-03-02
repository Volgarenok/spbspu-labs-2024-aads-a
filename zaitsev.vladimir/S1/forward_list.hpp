#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <stdexcept>
#include <cstddef>
#include "node.hpp"
#include "forward_list_iterator.hpp"

namespace zaitsev
{
  template< typename T >
  class ForwardList
  {
    using node_t = Node< T >;
  public:
    ForwardList();
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other);
    ForwardList(size_t count, const T& value);
    ~ForwardList();
    ForwardListIterator< T > begin();
    ForwardListIterator< T > end();
    bool empty() const;
    T& front();
    const T& front() const;
    void push_front(const T& value);
    void pop_front();
    void clear();
    void assign(size_t count, const T& value);
    void swap(ForwardList& other);
    void reverse();
    size_t remove(const T& value);
    template< class UnaryPredicate >
    size_t remove_if(UnaryPredicate p);
    void merge(ForwardList& other);
    size_t unique();
  private:
    node_t* head_;
  };

  template< typename T >
  ForwardList<T>::ForwardList():
    head_(nullptr)
  {}

  template<typename T>
  ForwardList<T>::ForwardList(size_t count, const T& value)
  {
    node_t* head = new node_t(value);
    head_ = head;
    try
    {
      for (size_t i = 1; i < count; ++i)
      {
        head->next_ = new node_t(value);
        head = head->next_;
      }
    }
    catch (const std::bad_alloc&)
    {
      freeNodes(head);
      throw;
    }
  }

  template< typename T >
  ForwardList<T>::ForwardList(const ForwardList& other)
  {
    if (!other.head_)
    {
      head_ = nullptr;
      return;
    }
    head_ = new node_t(other.head_->value_);
    node_t* head = head_;
    node_t* cur = other.head_->next_;
    try
    {
      while (cur)
      {
        head->next_ = new node_t(cur->value_);
        head = head->next_;
        cur = cur->next_;
      }
    }
    catch (const std::bad_alloc&)
    {
      freeNodes(head_);
      throw;
    }
  }

  template< typename T >
  ForwardList<T>::ForwardList(ForwardList&& other)
  {
    head_ = other.head_;
    other.head_ = nullptr;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    freeNodes(head_);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList<T>::begin()
  {
    return ForwardListIterator< T >(head_);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList<T>::end()
  {
    return ForwardListIterator< T >();
  }

  template< typename T >
  void ForwardList< T >::push_front(const T& value)
  {
    node_t* new_head = new node_t(value);
    new_head->next_ = head_;
    head_ = new_head;
  }

  template< typename T >
  void ForwardList< T >::pop_front()
  {
    if (!head_)
    {
      throw std::runtime_error("List is empty");
    }
    node_t* temp = head_;
    head_ = head_->next;
    delete head_;
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    freeNodes(head_);
  }

  template< typename T >
  void ForwardList< T >::assign(size_t count, const T& value)
  {
    node_t* new_head = nullptr;
    try
    {
      for (size_t i = 0; i < count; ++i)
      {
        node_t* temp = new node_t(value);
        temp->next_ = new_head;
        new_head = temp;
      }
    }
    catch(const std::bad_alloc&)
    {
      freeNodes(new_head);
    }
    freeNodes(head_);
    head_ = new_head;
  }

  template< typename T >
  bool ForwardList< T >::empty() const
  {
    return !head_;
  }

  template< typename T >
  T& ForwardList< T >::front()
  {
    return head_->value_;
  }

  template< typename T >
  const T& ForwardList< T >::front() const
  {
    return head_->value_;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T >& other)
  {
    node_t* temp = other.head_;
    other.head_ = head_;
    head_ = temp;
  }

  template< typename T >
  void ForwardList< T >::reverse()
  {
    if (!head_)
    {
      return;
    }
    Node< T >* new_head = head_;
    Node< T >* tail = head_->next_;
    new_head->next_ = nullptr;
    while (tail)
    {
      Node< T >* temp = tail->next_;
      tail->next_=new_head;
      new_head = tail;
      tail = temp;
    }
    head_ = new_head;
  }

  template<typename T>
  size_t ForwardList<T>::remove(const T& value)
  {
    size_t removed = 0;
    node_t* prev = nullptr;
    node_t* cur = head_;
    while (cur)
    {
      if (cur->value_ == value)
      {
        node_t* temp = cur;
        if (prev)
        {
          prev->next_ = cur->next_;
        }
        else
        {
          head_ = cur->next_;
        }
        cur = cur->next_;
        delete temp;
        ++removed;
      }
      else
      {
        prev = cur;
        cur = cur->next_;
      }
    }
    return removed;
  }

  template< typename T >
  void ForwardList< T >::merge(ForwardList< T >& other)
  {
    if (!other.head_)
    {
      return;
    }
    if (!head_)
    {
      head_ = other.head_;
      other.head_ = nullptr;
    }
    node_t* res = nullptr;
    node_t* list1_cur = head_;
    node_t* list2_cur = other.head_;
    if (list1_cur->value_ < list2_cur->value_)
    {
      res = list2_cur;
      list2_cur = list2_cur->next_;
    }
    else
    {
      res = list1_cur;
      list1_cur = list1_cur->next_;
    }

    while (list1_cur || list2_cur)
    {
      if (list1_cur && list2_cur)
      {
        if (list1_cur->value_ < list2_cur->value_)
        {
          res->next_ = list2_cur;
          list2_cur = list2_cur->next_;
        }
        else
        {
          res->next_ = list1_cur;
          list1_cur = list1_cur->next_;
        }
      }
      else if (list1_cur)
      {
        res->next_ = list1_cur;
        list1_cur = nullptr;
      }
      else
      {
        res->next_ = list2_cur;
        list2_cur = nullptr;
      }
    }
    head_ = res;
    other.head_ = nullptr;
  }

  template< typename T >
  size_t ForwardList< T >::unique()
  {
    if (!head_)
    {
      return 0;
    }
    size_t removed = 0;
    node_t* cur = head_;
    while (cur->next_)
    {
      if (cur->value_ == cur->next_->value_)
      {
        node_t* temp = cur->next_;
        cur->next_ = cur->next_->next_;
        delete temp;
        ++removed;
      }
      cur = cur->next_;
    }
    return removed;
  }
  template< typename T >
  template< typename UnaryPredicate >
  size_t ForwardList< T >::remove_if(UnaryPredicate p)
  {
    size_t removed = 0;
    node_t* prev = nullptr;
    node_t* cur = head_;
    while (cur)
    {
      if (p(cur->value_))
      {
        node_t* temp = cur;
        if (prev)
        {
          prev->next_ = cur->next_;
        }
        else
        {
          head_ = cur->next_;
        }
        cur = cur->next_;
        delete temp;
        ++removed;
      }
      else
      {
        prev = cur;
        cur = cur->next_;
      }
    }
    return removed;
  }
}
#endif
