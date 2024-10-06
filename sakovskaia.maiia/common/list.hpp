#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>
#include "iterator.hpp"
#include "const_iterator.hpp"
namespace sakovskaia
{
  template < typename T >
  class List
  {
  public:
    using iterator = fwdIterator< T >;
    using const_iterator = CFwdIterator< T >;
    List();
    ~List();
    List(const List & other);
    List(List && other) noexcept;
    List & operator=(const List & other);
    List & operator=(List && other) noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    void push_front(const T & value);
    void push_back(const T & value);
    void pop_front();
    void clear();
    void swap(List< T > & other) noexcept;
    T & front() noexcept;
    const T & front() const noexcept;
  private:
    node_t< T > * head_;
    void copy_from(const List & other);
    void move_from(List && other) noexcept;
  };

  template< typename T >
  List< T >::List():
   head_(nullptr)
  {}

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  List< T >::List(const List & other):
   head_(nullptr)
  {
    try
    {
      copy_from(other);
    }
    catch(...)
    {
      clear();
      throw;
    }
  }

  template< typename T >
  List< T >::List(List && other) noexcept:
   head_(nullptr)
  {
    move_from(std::move(other));
  }

  template< typename T >
  List< T > & List< T >::operator=(const List & other)
  {
    if (this != std::addressof(other))
    {
      clear();
      copy_from(other);
    }
    return * this;
  }

  template< typename T >
  List< T > & List< T >::operator=(List && other) noexcept
  {
    if (this != std::addressof(other))
    {
      clear();
      move_from(std::move(other));
    }
    return * this;
  }

  template< typename T >
  typename List< T >::iterator List< T >::begin() noexcept
  {
    return iterator(head_);
  }

  template< typename T >
  typename List< T >::iterator List< T >::end() noexcept
  {
    return iterator(nullptr);
  }

  template< typename T >
  typename List< T >::const_iterator List< T >::begin() const noexcept
  {
    return const_iterator(head_);
  }

  template< typename T >
  typename List< T >::const_iterator List< T >::end() const noexcept
  {
    return const_iterator(nullptr);
  }

  template< typename T >
  typename List< T >::const_iterator List< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }

  template< typename T >
  typename List< T >::const_iterator List< T >::cend() const noexcept
  {
    return const_iterator(nullptr);
  }

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template< typename T >
  void List< T >::push_front(const T & value)
  {
    node_t< T > * new_node = new node_t< T >(value);
    new_node->next = head_;
    head_ = new_node;
  }

  template< typename T >
  void List< T >::push_back(const T & value)
  {
    node_t< T > * new_node = new node_t< T >(value);
    if (!head_)
    {
      head_ = new_node;
    }
    else
    {
      node_t< T > * current = head_;
      while (current->next)
      {
        current = current->next;
      }
      current->next = new_node;
    }
  }

  template< typename T >
  void List< T >::pop_front()
  {
    if (head_)
    {
      node_t< T > * temp = head_;
      head_ = head_->next;
      delete temp;
    }
  }

  template< typename T >
  void List< T >::clear()
  {
    while (head_)
    {
      pop_front();
    }
  }

  template< typename T >
  void List< T >::copy_from(const List & other)
  {
    if (other.head_)
    {
      head_ = new node_t< T >(other.head_->data);
      node_t< T > * current = head_;
      node_t< T > * other_current = other.head_->next;
      while (other_current)
      {
        current->next = new node_t< T >(other_current->data);
        current = current->next;
        other_current = other_current->next;
      }
    }
  }

  template< typename T >
  void List< T >::move_from(List && other) noexcept
  {
    head_ = other.head_;
    other.head_ = nullptr;
  }

  template< typename T >
  T & List< T >::front() noexcept
  {
    if (empty())
    {
      throw std::runtime_error("List is empty");
    }
    return head_->data;
  }

  template< typename T >
  const T & List< T >::front() const noexcept
  {
    if (empty())
    {
      throw std::runtime_error("List is empty");
    }
    return head_->data;
  }
}
#endif
