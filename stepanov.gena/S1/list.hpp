#ifndef LIST_HPP
#define LIST_HPP

#include <utility>
#include <cstddef>
#include <stdexcept>
#include "node.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"

namespace stepanov
{
  template < typename T >
  class Iterator;

  template < typename T >
  class ConstIterator;

  template < typename T >
  class List
  {
    friend class Iterator< T >;
    friend class ConstIterator< T >;

  public:
    using iterator = Iterator< T >;
    using const_iterator = ConstIterator< T >;

    List();
    List(const List & other);
    List(List && other) noexcept;
    explicit List(size_t n);
    List(size_t n, const T & value);
    ~List();

    List & operator=(const List & other);
    List & operator=(List && other) noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    T & front();
    const T & front() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    T & operator[](size_t index);
    const T & operator[](size_t index) const;

    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void pop_front();
    void clear() noexcept;
    void swap(List & fwdlst);

    void remove(const T & value);
    template < typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t n, const T & value);

  private:
    Node<T> * head_;
    Node<T> * tail_;
  };

  template < typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  List< T >::List(const List & other):
    List()
  {
    Node< T > * newnode = other.head_;
    while (newnode)
    {
      push_back(newnode->data_);
      newnode = newnode->next_;
    }
  }

  template < typename T >
  List< T >::List(List && other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template < typename T >
  List< T >::List(size_t n):
    List(n, T())
  {}

  template < typename T >
  List< T >::List(size_t n, const T & value):
    List()
  {
    for (size_t i = 0; i < n; ++i)
    {
      push_back(value);
    }
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  List< T > & List< T >::operator=(const List & other)
  {
    if (this != std::addressof(other))
    {
      List< T > copy{other};
      swap(copy);
    }
    return *this;
  }

  template < typename T >
  List< T > & List< T >::operator=(List && other) noexcept
  {
    if (this != std::addressof(other))
    {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      other.head_ = nullptr;
      other.tail_ = nullptr;
    }
    return *this;
  }

  template < typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return iterator(head_);
  }

  template < typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return iterator();
  }

  template < typename T >
  ConstIterator< T > List< T >::begin() const noexcept
  {
    return const_iterator(head_);
  }

  template < typename T >
  ConstIterator< T > List< T >::end() const noexcept
  {
    return const_iterator();
  }

  template < typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }

  template < typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return const_iterator();
  }

  template <  typename T >
  T & List< T >::front()
  {
    return head_->data_;
  }

  template < typename T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template <typename T>
  size_t List<T>::size() const noexcept
  {
    size_t count = 0;
    Node<T> *current = head_;
    while (current != nullptr)
    {
      ++count;
      current = current->next_;
    }
    return count;
  }

  template <typename T>
  T& List<T>::operator[](size_t index)
  {
    if (index >= size())
    {
      throw std::out_of_range("Index out of range");
    }
    Node<T> *current = head_;
    for (size_t i = 0; i < index; ++i)
    {
      current = current->next_;
    }
    return current->data_;
  }

  template <typename T>
  const T& List<T>::operator[](size_t index) const
  {
    if (index >= size())
    {
      throw std::out_of_range("Index out of range");
    }
    Node<T> *current = head_;
    for (size_t i = 0; i < index; ++i)
    {
      current = current->next_;
    }
    return current->data_;
  }

  template < typename T >
  void List< T >::push_front(const T & value)
  {
    Node< T > * newnode = new Node< T >(value);
    newnode->next_ = head_;
    head_ = newnode;
    if (tail_ == nullptr)
    {
      tail_ = newnode;
    }
  }

  template < typename T >
  void List< T >::push_front(T && value)
  {
    Node< T > * newnode = new Node< T >(std::move(value));
    newnode->next_ = head_;
    head_ = newnode;
    if (tail_ == nullptr)
    {
      tail_ = newnode;
    }
  }

  template < typename T >
  void List< T >::push_back(const T & value)
  {
    Node< T > * newnode = new Node< T >(value);
    if (empty())
    {
      head_ = newnode;
      tail_ = newnode;
      return;
    }
    tail_->next_ = newnode;
    tail_ = newnode;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (head_ == nullptr)
    {
      return;
    }
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    Node< T > * newhead = head_->next_;
    delete head_;
    head_ = newhead;
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
  void List< T >::swap(List< T > & list)
  {
    Node< T > * subhead = head_;
    Node< T > * subtail = tail_;
    head_ = list.head_;
    tail_ = list.tail_;
    list.head_ = subhead;
    list.tail_ = subtail;
  }

  template < typename T >
  void List< T >::remove(const T & value)
  {
    while (head_ != nullptr && head_->data_ == value)
    {
      Node< T >* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    if (head_ == nullptr)
    {
      tail_ = nullptr;
      return;
    }
    Node< T > * current = head_;
    while (current->next_ != nullptr)
    {
      if (current->next_->data_ == value)
      {
        Node< T >* temp = current->next_;
        current->next_ = current->next_->next_;
        delete temp;
        if (current->next_ == nullptr)
        {
          tail_ = current;
        }
      }
      else
      {
        current = current->next_;
      }
    }
  }

  template < typename T >
  template < typename Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    while (head_ != nullptr && pred(head_->data_))
    {
      Node< T > * temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    if (head_ == nullptr)
    {
      tail_ = nullptr;
      return;
    }
    Node< T > * current = head_;
    while (current->next_ != nullptr)
    {
      if (pred(current->next_->data_))
      {
        Node< T > * temp = current->next_;
        current->next_ = current->next_->next_;
        delete temp;
        if(pred(current->next_ == nullptr))
        {
          tail_ = current;
        }
      }
      else
      {
        current = current->next_;
      }
    }
  }

  template < typename T >
  void List< T >::assign(size_t n, const T & value)
  {
    clear();
    if (n == 0)
    {
        return;
    }
    for (size_t i = 0; i < n; ++i)
    {
      push_back(value);
    }
  }
}

#endif
