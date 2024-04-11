#ifndef LIST_HPP
#define LIST_HPP

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
    void pop_back();
    void clear();
    bool empty() const;
    void swap(List& other);
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
      Node< T >* head_;
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
    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

  template< typename T >
  List< T >::List(const List& other):
    size_(other.size_),
    head_(other.head_)
  {
    Node< T >* current = other.head_;
    while (current != nullptr)
    {
      push_back(current->data);
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
      swap(prev);
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other) noexcept
  {
    List< T > prev(std::move(other));
    if (std::addressof(other) != this)
    {
      swap(prev);
    }
    return *this;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    Node< T >* temp = new Node< T >(data);
    temp->next = head_;
    head_ = temp;
    ++size_;
  }

  template< typename T >
  void List< T >::push_back(T data)
  {
    Node< T >* newNode = new Node< T >(data);
    if (empty())
    {
      head_ = newNode;
    }
    else
    {
      Node< T >* head = head_;
      while (head->next)
      {
          head = head->next;
      }
      head->next = newNode;
    }
   ++size_;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!(empty()))
    {
      pop_front();
    }
    size_ = 0;
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
    Node< T >* head = head_;
    head_ = head_->next;
    delete head;
    --size_;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    if (empty())
    {
      throw;
    }
    if (head_->next == nullptr)
    {
      delete head_;
      head_ = nullptr;
    }
    else
    {
      Node< T >* head = head_;
      while (head->next->next != nullptr)
      {
        head = head->next;
      }
      delete head->next;
      head->next = nullptr;
    }
    --size_;
  }

  template< typename T >
  void List< T >::swap(List& other)
  {
    std::swap(head_, other.head_);
  }

  template< typename T >
  void List< T >::reverse()
  {
    if (!head_)
    {
      return;
    }
    Node< T >* result = head_;
    Node< T >* temp = head_->next;
    result->next = nullptr;
    while (temp)
    {
      Node< T >* rofl = temp->next;
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
    Node< T >* current = head_;
    Node< T >* prev = nullptr;

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
    List< T > prev;
    try
    {
      for (size_t i = 0; i < count; ++i)
      {
        prev.push_front(value);
      }
      prev.reverse();
      swap(prev);
    }
    catch (...)
    {
      throw;
    }
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
