#ifndef LIST_HPP
#define LIST_HPP

#include <utility>
#include <memory>
#include <stdexcept>
#include "node.hpp"
#include "constIterator.hpp"


namespace sivkov
{
  template < typename T >
  class List
  {
  public:
    List();
    List(size_t count, const T& value);
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other) noexcept;

    void push_front(const T& data);
    void push_back(T data);
    void pop_front();
    void clear() noexcept;
    bool empty() const;
    void swap(List& other) noexcept;
    void reverse();
    size_t getSize();
    void remove(const T& value);
    template< class Predicate >
    void remove_if(Predicate p);
    void assign(size_t count, const T& value);
    T& front();
    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;

  private:
    size_t size_;
    detail::Node< T >* head_;
  };

  template< typename T >
  List< T >::List():
    size_(0),
    head_(nullptr)
  {}

  template< typename T >
  List< T >::List(size_t count, const T& value):
    size_(0),
    head_(nullptr)
  {
    assign(count, value);
  }

  template< typename T >
  List< T >::List(const List& other):
    List()
  {
    detail::Node< T >* current = other.head_;
    while (current)
    {
      push_front(current->data);
      current = current->next;
    }
  }

  template< typename T >
  List< T >::List(List&& other) noexcept:
    size_(other.size_),
    head_(other.head_)
  {
    other.head_ = nullptr;
    other.size_ = 0;
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    List< T > prev(other);
    if (std::addressof(other) != this)
    {
      List< T > prev(other);
      swap(prev);
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      List< T > prev(std::move(other));
      swap(prev);
    }
    return *this;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    detail::Node< T >* temp = new detail::Node< T >(data);
    temp->next = head_;
    head_ = temp;
    ++size_;
  }

  template< typename T >
  void List< T >::push_back(T data)
  {
    detail::Node< T >* newNode = new detail::Node< T >(data);
    if (empty())
    {
      head_ = newNode;
    }
    else
    {
      detail::Node< T >* head = head_;
      while (head->next)
      {
        head = head->next;
      }
      head->next = newNode;
    }
    ++size_;
  }

  template< typename T >
  void List< T >::clear() noexcept
  {
    while (!(empty()))
    {
      pop_front();
    }
  }

  template< typename T >
  bool List< T >::empty() const
  {
    return head_ == nullptr;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    if (empty())
    {
      throw std::logic_error("empty");
    }
    detail::Node< T >* head = head_;
    head_ = head_->next;
    delete head;
    --size_;
  }

  template< typename T >
  void List< T >::swap(List& other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void List< T >::reverse()
  {
    if (!head_)
    {
      return;
    }
    detail::Node< T >* result = head_;
    detail::Node< T >* temp = head_->next;
    result->next = nullptr;
    while (temp)
    {
      detail::Node< T >* rofl = temp->next;
      temp->next = result;
      result = temp;
      temp = rofl;
    }
    head_ = result;
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
    auto pred = [&value](const T& elem)
    {
      return elem == value;
    };
    remove_if(pred);
  }

  template< typename T >
  template< class Predicate >
  void List< T >::remove_if(Predicate p)
  {
    detail::Node< T >* current = head_;
    detail::Node< T >* prev = nullptr;

    while (current != nullptr)
    {
      if (p(current->data))
      {
        if (prev == head_)
        {
          pop_front();
          current = head_;
        }
        else
        {
          prev->next = current->next;
          delete current;
          current = prev->next;
        }
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template< typename T >
  void List< T >::assign(size_t count, const T& value)
  {
    List< T > assignList;
    for (size_t i = 0; i < count; ++i)
    {
      assignList.push_back(value);
    }
    swap(assignList);
  }

  template< typename T >
  size_t List< T >::getSize()
  {
    return size_;
  }

  template< typename T >
  T& List< T >::front()
  {
    return head_->data;
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >(nullptr);
  }
}
#endif

