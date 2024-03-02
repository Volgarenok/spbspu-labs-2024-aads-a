#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

#include "iterator.hpp"
#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    List();
    List(const List< T > &);
    List(List< T > &&);
    ~List();

    List< T > &operator=(List< T > &&);
    List< T > &operator=(const List< T > &);

    T &front();
    T &back();

    size_t capacity();
    bool empty();

    void push_back(const T &);
    void push_front(const T &);

    void pop_back();
    void pop_front();
    void clear();
    void swap(List< T > &other);

    iterator begin();
    iterator end();

  private:
    size_t m_size;
    Node< T > *m_head;
    Node< T > *m_tail;
  };

  template < typename T >
  List< T >::List():
    m_size(0),
    m_head(nullptr),
    m_tail(nullptr)
  {}

  template < typename T >
  List< T >::List(const List< T > &other):
    m_size(0),
    m_head(nullptr),
    m_tail(nullptr)
  {
    Node< T > *node = other.m_head;
    while (node != nullptr)
    {
      push_back(node->value);
      node = node->next;
    }
  }

  template < typename T >
  List< T >::List(List< T > &&other):
    m_size(other.m_size),
    m_head(other.m_head),
    m_tail(other.m_tail)
  {
    other.m_size = 0;
    other.m_head = nullptr;
    other.m_tail = nullptr;
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  List< T > &List< T >::operator=(List< T > &&other)
  {
    clear();
    m_size = other.m_size;
    m_head = other.m_head;
    m_tail = other.m_tail;
    other.m_size = 0;
    other.m_head = nullptr;
    other.m_tail = nullptr;
    return *this;
  }

  template < typename T >
  List<T> & List<T>::operator=(const List<T> &other)
  {
    m_size = other.m_size;
    m_head = other.m_head;
    m_tail = other.m_tail;
    Node< T > *node = other.m_head;
    while (node != nullptr)
    {
      push_back(node->value);
      node = node->next;
    }
    return *this;
  }

  template < typename T >
  T &List< T >::front()
  {
    return m_head->value;
  }

  template < typename T >
  T &List< T >::back()
  {
    return m_tail->value;
  }

  template < typename T >
  size_t List< T >::capacity()
  {
    return m_size;
  }

  template < typename T >
  bool List< T >::empty()
  {
    return m_size == 0;
  }

  template < typename T >
  void List< T >::push_back(const T &value)
  {
    auto newTail = new Node< T >(value, m_tail, nullptr);
    if (m_head != nullptr)
    {
      m_tail->next = newTail;
      m_tail = newTail;
    }
    else
    {
      m_head = newTail;
      m_tail = newTail;
    }
    m_size++;
  }

  template < typename T >
  void List< T >::push_front(const T &value)
  {
    auto newHead = new Node< T >(value, m_head, nullptr);
    if (m_head != nullptr)
    {
      m_head->prev = newHead;
      m_head = newHead;
    }
    else
    {
      m_head = newHead;
      m_tail = newHead;
    }
    m_size++;
  }

  template < typename T >
  void List< T >::pop_back()
  {
    if (empty())
    {
      throw std::underflow_error("calling 'pop' in already empty list");
    }
    Node< T > prev = m_tail->prev;
    delete m_tail;
    m_tail = prev;
    --m_size;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (empty())
    {
      throw std::underflow_error("calling 'pop' in already empty list");
    }
    Node< T > *next = m_head->next;
    delete m_head;
    m_head = next;
    --m_size;
  }

  template < typename T >
  void List< T >::clear()
  {
    Node< T > *currNode = m_head;
    Node< T > *nextNode = nullptr;
    while (currNode)
    {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
    }
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
  }

  template < typename T >
  void List< T >::swap(List< T > &other)
  {
    List< T > temp(std::move(*this));
    *this = std::move(other);
    other = std::move(temp);
  }

  template < typename T >
  typename List< T >::iterator List< T >::begin()
  {
    return iterator(m_head);
  }

  template < typename T >
  typename List< T >::iterator List< T >::end()
  {
    return iterator(nullptr);
  }
}

#endif
