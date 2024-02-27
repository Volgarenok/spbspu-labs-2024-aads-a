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
    ~List();

    size_t capacity();
    bool empty();

    void push_back(T &&);
    void push_front(T &&);

    void pop_back();
    void pop_front();
    void clear();

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
  List< T >::~List()
  {
    clear();
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
  void List< T >::push_back(T &&value)
  {
    Node< T > *newTail = new Node< T >(std::forward< T >(value), m_tail, nullptr);
    if (empty)
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
  void List< T >::push_front(T &&value)
  {
    Node< T > *newHead = new Node< T >(std::forward< T >(value), m_head, nullptr);
    if (empty)
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
    if (empty)
    {
      throw std::underflow_error("calling 'pop' in already empty list");
    }
    Node< T > prev = m_tail->prev;
    delete m_tail;
    m_tail = prev;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    if (empty)
    {
      throw std::underflow_error("calling 'pop' in already empty list");
    }
    Node< T > next = m_head->next;
    delete m_head;
    m_head = next;
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
