#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace vyzhanov
{
  template<typename T>
  struct List
  {
    using citerator = ConstBiIterator< T >;
    using iterator = BiIterator< T >;

    List();
    ~List();

    void clear();
    bool empty();

    size_t capacity() const noexcept;
    void swap(List< T >&) noexcept;

    void assign(size_t count, const T&);
    void assign(iterator, iterator);
    void assign(std::initializer_list<T>);

    void push_back(const T&);
    void push_back(T&&);
    void push_front(const T&);
    void push_front(T&&);

    void pop_back();
    void pop_front();

    T& back();
    T& front();
    const T& back() const;
    const T& front() const;

    iterator begin() noexcept;
    citerator cbegin() const noexcept;
    iterator end() noexcept;
    citerator cend() const noexcept;
  private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
  };

  template< class T >
  List< T >::List() :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T>
  void List<T>::clear()
  {
    while (head_ != tail_)
    {
      Node< T >* newHead = head_->next_;
      delete head_;
      head_ = newHead;
    }
  }

  template < typename T>
  bool List<T>::empty()
  {
    return (head_ = tail_);
  }

  template < typename T>
  size_t List<T>::capacity() const noexcept
  {
    return size_;
  }

  template < typename T>
  void List<T>::swap(List< T >& list) noexcept
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
  }

  template< class T >
  void List< T >::assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; i++)
    {
      push_back(value);
    }
  }

  template < typename T >
  void List< T >::assign(iterator first, iterator last)
  {
    clear();
    while (first != last)
    {
      push_back(*first);
      first++;
    }
  }

  template < typename T >
  void List< T >::assign(std::initializer_list< T > list)
  {
    clear();
    typename std::initializer_list< T >::iterator list_begin = list.begin();
    while (list_begin != list.end())
    {
      push_back(*list_begin);
      list_begin++;
    }
  }

  template < typename T>
  void List<T>::push_back(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, nullptr, tail_);
    newNode->prev_ = tail_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
    }
    tail_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::push_back(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    newNode->prev_ = tail_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
    }
    tail_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::push_front(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, head_, nullptr);
    newNode->next_ = head_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      head_->prev_ = newNode;
    }
    head_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::push_front(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    newNode->next_ = head_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      head_->next_ = newNode;
    }
    head_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::pop_back()
  {
    Node< T >* newTail = tail_->prev_;
    if (tail_ == head_)
    {
      return;
    }
    else
    {
      newTail->next_ = nullptr;
    }
    tail_ = newTail;
    --size_;
  }

  template < typename T>
  void List<T>::pop_front()
  {
    Node< T >* newHead = head_->next_;
    if (head_ == tail_)
    {
      return;
    }
    else
    {
      newHead->prev_ = nullptr;
    }
    head_ = newHead;
    --size_;
  }

  template < typename T>
  T& List<T>::back()
  {
    return tail_->data_;
  }

  template < typename T>
  T& List<T>::front()
  {
    return head_->data_;
  }

  template < typename T>
  const T& List<T>::back() const
  {
    return tail_->data_;
  }

  template < typename T>
  const T& List<T>::front() const
  {
    return head_->data_;
  }

  template < typename T>
  BiIterator<T> List<T>::begin() noexcept
  {
    return iterator(head_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cbegin() const noexcept
  {
    return citerator(head_);
  }

  template < typename T>
  BiIterator<T> List<T>::end() noexcept
  {
    return iterator(tail_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cend() const noexcept
  {
    return citerator(tail_);
  }
}
#endif
