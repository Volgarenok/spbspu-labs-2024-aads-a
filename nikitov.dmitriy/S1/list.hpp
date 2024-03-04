#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include <initializer_list>
#include "list_iterator.hpp"
#include "const_list_iterator.hpp"

namespace nikitov
{
  template< typename T >
  struct Node
  {
  public:
    Node();
    Node(T value);
    ~Node() = default;
    T value_;
    Node* prev_;
    Node* next_;
  };

  template< typename T >
  class List
  {
    using iterator = ListIterator< T >;
    using constIterator = ConstListIterator< T >;
  public:
    List();
    List(size_t n, const T& value);
    List(constIterator first, constIterator second);
    List(const List< T >& other);
    List(List< T >&& other);
    List(std::initializer_list< T > initList);
    ~List();

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other);

    bool operator==(const List< T >& other) const;
    bool operator!=(const List< T >& other) const;
    bool operator<(const List< T >& other) const;
    bool operator>(const List< T >& other) const;
    bool operator<=(const List< T >& other) const;
    bool operator>=(const List< T >& other) const;

    iterator begin();
    constIterator cbegin() const;
    iterator end();
    constIterator cend() const;

    T& front();
    T& back();

    size_t size() const;
    bool empty() const;

    void assign(constIterator first, constIterator second);
    void assign(size_t n, const T& value);
    void assign(std::initializer_list< T > initList);
    void push_front(const T& value);
    void pop_front();
    void push_back(const T& value);
    void pop_back();
    iterator insert(constIterator position, const T& value);
    void clear();
    void swap(List< T >& other);

    void remove(const T& value);
    template< typename Predicate >
    void remove_if(Predicate pred);

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };

  template< typename T >
  Node< T >::Node():
    value_(T()),
    prev_(nullptr),
    next_(nullptr)
  {}

  template< typename T >
  Node< T >::Node(T value):
    value_(value),
    prev_(nullptr),
    next_(nullptr)
  {}

  template< typename T >
  List< T >::List():
    head_(new Node< T >),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  List< T >::List(size_t n, const T& value):
    head_(new Node< T >),
    tail_(nullptr),
    size_(0)
  {
    for (size_t i = 0; i != n; ++i)
    {
      push_back(value);
    }
  }

  template< typename T >
  List< T >::List(constIterator first, constIterator second):
    head_(new Node< T >),
    tail_(nullptr),
    size_(0)
  {
    for (auto i = first; i != second; ++i)
    {
      push_back(*i);
    }
  }

  template< typename T >
  List< T >::List(const List< T >& other):
    head_(new Node< T >),
    tail_(nullptr),
    size_(0)
  {
    Node< T >* node = other.head_;
    for (size_t i = 0; i != other.size_; ++i)
    {
      push_back(node->value_);
      node = node->next_;
    }
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  template< typename T >
  List< T >::List(std::initializer_list< T > initList):
    head_(new Node< T >),
    tail_(nullptr),
    size_(0)
  {
    for (T value : initList)
    {
      push_back(value);
    }
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete head_;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    List< T > temp(other);
    if (std::addressof(other) != this)
    {
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other)
  {
    List< T > temp(std::move(other));
    if (std::addressof(other) != this)
    {
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  bool List< T >::operator==(const List< T >& other) const
  {
    if (size_ == other.size_)
    {
      auto otherIterator = other.cbegin();
      for (auto ownIterator = cbegin(); ownIterator != cend(); ++ownIterator)
      {
        if (*ownIterator != *otherIterator)
        {
          return false;
        }
        ++otherIterator;
      }
    }
    else
    {
      return false;
    }
    return true;
  }

  template< typename T >
  bool List< T >::operator!=(const List< T >& other) const
  {
    return !(*this == other);
  }

  template< typename T >
  bool List< T >::operator<(const List< T >& other) const
  {
    auto otherIterator = other.cbegin();
    for (auto ownIterator = cbegin(); ownIterator != cend(); ++ownIterator)
    {
        if (otherIterator == other.cend())
        {
          return false;
        }
        if (*ownIterator < *otherIterator)
        {
          return true;
        }
        else if (*ownIterator > *otherIterator)
        {
          return false;
        }
        ++otherIterator;
    }
    return false;
  }

  template< typename T >
  bool List< T >::operator>(const List< T >& other) const
  {
    return !(*this < other);
  }

  template< typename T >
  bool List< T >::operator<=(const List< T >& other) const
  {
    return (*this < other || *this == other);
  }

  template< typename T >
  bool List< T >::operator>=(const List< T >& other) const
  {
    return (*this > other || *this == other);
  }

  template< typename T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(head_);
  }

  template< typename T >
  ConstListIterator< T > List< T >::cbegin() const
  {
    return ConstListIterator< T >(head_);
  }

  template< typename T >
  ListIterator< T > List< T >::end()
  {
    if (tail_ == nullptr)
    {
      return ListIterator< T >(head_);
    }
    else
    {
      return ListIterator< T >(tail_->next_);
    }
  }

  template< typename T >
  ConstListIterator< T > List< T >::cend() const
  {
    if (tail_ == nullptr)
    {
      return ConstListIterator< T >(head_);
    }
    else
    {
      return ConstListIterator< T >(tail_->next_);
    }
  }

  template< typename T >
  T& List< T >::front()
  {
    return head_->value_;
  }

  template< typename T >
  T& List< T >::back()
  {
    return tail_->value_;
  }

  template< typename T >
  size_t List< T >::size() const
  {
    return size_;
  }

  template< typename T >
  bool List< T >::empty() const
  {
    return !size_;
  }

  template< typename T >
  void List< T >::assign(constIterator first, constIterator second)
  {
    clear();
    for (auto i = first; i != second; ++i)
    {
      push_back(*i);
    }
  }

  template< typename T >
  void List< T >::assign(size_t n, const T& value)
  {
    clear();
    for (size_t i = 0; i != n; ++i)
    {
      push_back(value);
    }
  }

  template< typename T >
  void List< T >::assign(std::initializer_list< T > initList)
  {
    clear();
    for (T value : initList)
    {
      push_back(value);
    }
  }

  template< typename T >
  void List< T >::push_front(const T& value)
  {
    Node< T >* ptr = new Node< T >(value);
    ptr->next_ = head_;
    if (head_->next_ != nullptr)
    {
      head_->prev_ = ptr;
    }
    else
    {
      ptr->next_ = head_;
      head_->prev_ = ptr;
      tail_ = ptr;
    }
    head_ = ptr;
    ++size_;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    Node< T >* ptr = head_->next_;
    if (ptr->next_ != nullptr)
    {
      ptr->prev_ = nullptr;
    }
    else
    {
      ptr->prev_ = nullptr;
      tail_ = nullptr;
    }
    delete head_;
    head_ = ptr;
    --size_;
  }

  template< typename T >
  void List< T >::push_back(const T& value)
  {
    Node< T >* ptr = new Node< T >(value);
    ptr->prev_ = tail_;
    if (tail_ != nullptr)
    {
      ptr->next_ = tail_->next_;
      ptr->next_->prev_ = ptr;
      tail_->next_ = ptr;
    }
    else
    {
      ptr->next_ = head_;
      head_->prev_ = ptr;
      head_ = ptr;
    }
    tail_ = ptr;
    ++size_;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    Node< T >* ptr = tail_->prev_;
    if (ptr != nullptr)
    {
      ptr->next_ = tail_->next_;
      ptr->next_->prev_ = ptr;
    }
    else
    {
      head_ = tail_->next_;
      head_->prev_ = nullptr;
    }
    delete tail_;
    tail_ = ptr;
    --size_;
  }

  template< typename T >
  ListIterator< T > List< T >::insert(ConstListIterator< T > position, const T& value)
  {
    if (position == cbegin())
    {
      push_front(value);
      return begin();
    }
    else if (position == cend())
    {
      push_back(value);
      return --end();
    }
    else
    {
      auto iterator = begin();
      Node< T >* node = head_;
      while (iterator != position)
      {
        ++iterator;
        node = node->next_;
      }
      Node< T >* newNode = new Node< T >(value);
      newNode->prev_ = node->prev_;
      newNode->next_ = node;
      newNode->prev_->next_ = newNode;
      node->prev_ = newNode;
      ++size_;
      return iterator;
    }
  }

  template< typename T >
  void List< T >::clear()
  {
    while (size_ >= 1)
    {
      pop_back();
    }
  }

  template< typename T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
    Node< T >* node = head_;
    while (node->next_ != nullptr)
    {
      Node < T >* temp = node->next_;
      while (node->value_ != value)
      {
        node = node->next_;
        if (node->next_ == nullptr)
        {
          return;
        }
      }
      if (node == head_)
      {
        pop_front();
      }
      else if (node == tail_)
      {
        pop_back();
        break;
      }
      else
      {
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        delete node;
        --size_;
      }
      node = temp;
    }
  }

  template< typename T >
  template< typename Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    Node< T >* node = head_;
    while (node->next_ != nullptr)
    {
      Node < T >* temp = node->next_;
      while (pred(node->value_))
      {
        node = node->next_;
        if (node->next_ == nullptr)
        {
          return;
        }
      }
      if (node == head_)
      {
        pop_front();
      }
      else if (node == tail_)
      {
        pop_back();
        break;
      }
      else
      {
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        delete node;
        --size_;
      }
      node = temp;
    }
  }
}
#endif
