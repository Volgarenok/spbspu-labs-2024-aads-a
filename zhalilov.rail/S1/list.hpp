#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>

#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class List {
  public:
    List();
    ~List();

    void push_back(T &&value);
    void push_front(T &&value);
    void clear();

  private:
    size_t m_size;
    Node < T > *m_head;
    Node < T > *m_tail;
  };

  template < typename T >
  List < T >::List():
    m_size(0),
    m_head(nullptr),
    m_tail(nullptr)
  {}

  template < typename T >
  List < T >::~List()
  {
    clear();
  }

  template < typename T >
  void List < T >::push_back(T &&value)
  {
    Node < T > *newTail = new Node < T >(std::forward < T >(value), m_tail, nullptr);
    if (m_size > 0)
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
  void List < T >::push_front(T &&value)
  {
    Node < T > *newHead = new Node < T >(std::forward < T >(value), m_head, nullptr);
    if (m_size > 0)
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
  void List < T >::clear()
  {
    Node < T > *currNode = m_head;
    Node < T > *nextNode = nullptr;
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
}

#endif
