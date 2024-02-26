#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <stdexcept>
#include <cstddef>
#include "node.hpp"

namespace zaitsev
{
  template< typename T >
  class ForwardList
  {
    using NodeT = Node< T >;
  public:
    ForwardList();
    ForwardList(size_t count, const T& value);
    ForwardList(const ForwardList& other);
    ~ForwardList();
    bool empty() const;
    T& front();
    const T& front() const;
    void push_front(const T& value);
    void pop_front();
    void clear();
    void assign(size_t count, const T& value);
    void swap(ForwardList& other);
  private:
    NodeT* head_;
  };

  template< typename T >
  ForwardList<T>::ForwardList():
    head_(nullptr)
  {}

  template<typename T>
  ForwardList<T>::ForwardList(size_t count, const T& value)
  {
    NodeT* head = new NodeT(value);
    head_ = head;
    try
    {
      for (size_t i = 1; i < count; ++i)
      {
        head->next_ = new NodeT(value);
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
    head_ = new NodeT(other.head_->value_);
    NodeT* head = head_;
    NodeT* cur = other.head_->next_;
    try
    {
      while (!cur)
      {
        head->next = new NodeT(cur->value);
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
  ForwardList< T >::~ForwardList()
  {
    freeNodes(head_);
  }

  template< typename T >
  void ForwardList< T >::push_front(const T& value)
  {
    NodeT* new_head = new Node(value);
    new_head->next = head_;
    head_ = new_head;
  }

  template< typename T >
  void ForwardList< T >::pop_front()
  {
    if (!head_)
    {
      throw std::runtime_error("List is empty");
    }
    NodeT* temp = head_;
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
    NodeT* new_head = nullptr;
    try
    {
      for (size_t i = 0; i < count; ++i)
      {
        NodeT* temp = new Node(value);
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
    return head_;
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
    NodeT* temp = other.head_;
    other.head_ = head_;
    head_ = temp;
  }
}
#endif 
