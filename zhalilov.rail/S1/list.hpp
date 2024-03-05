#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class Iterator
  {
  public:
    Iterator(Node< T > *);
    ~Iterator() = default;

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++();
    Iterator &operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    T &operator*();
    T *operator->();

    bool operator==(const Iterator< T > &);
    bool operator!=(const Iterator< T > &);

  private:
    Node< T > *m_node;
  };

  template < typename T >
  class ConstIterator
  {
  public:
    ConstIterator(Node< T > *);
    ~ConstIterator() = default;

    ConstIterator &operator=(const ConstIterator &) = default;

    ConstIterator &operator++();
    ConstIterator &operator--();
    ConstIterator operator++(int);
    ConstIterator operator--(int);

    const T &operator*();
    const T *operator->();

    bool operator==(const ConstIterator< T > &);
    bool operator!=(const ConstIterator< T > &);

    friend

  private:
    Node< T > *m_node;
  };

  template < typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using const_iterator = ConstIterator< T >;
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

    void insert(const_iterator, T &&);
    void push_back(const T &);
    void push_front(const T &);

    void pop_back();
    void pop_front();
    void clear();
    void swap(List< T > &other);

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

  private:
    size_t m_size;
    Node< T > *m_head;
    Node< T > *m_tail;
  };

  template < typename T >
  Iterator< T >::Iterator(Node< T > *node):
    m_node(node)
  {}

  template < typename T >
  Iterator< T > &Iterator< T >::operator++()
  {
    m_node = m_node->next;
    return *this;
  }

  template < typename T >
  Iterator< T > &Iterator< T >::operator--()
  {
    m_node = m_node->prev;
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator< T > temp(*this);
    operator++();
    return temp;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    Iterator< T > temp(*this);
    operator--();
    return temp;
  }

  template < typename T >
  T &Iterator< T >::operator*()
  {
    return m_node->value;
  }

  template < typename T >
  T *Iterator< T >::operator->()
  {
    return &m_node->value;
  }

  template < typename T >
  bool Iterator< T >::operator==(const Iterator< T > &it)
  {
    return m_node == it.m_node;
  }

  template < typename T >
  bool Iterator< T >::operator!=(const Iterator< T > &it)
  {
    return !operator==(it);
  }

  template < typename T >
  ConstIterator< T >::ConstIterator(Node< T > *node):
    m_node(node)
  {}

  template < typename T >
  ConstIterator< T > &ConstIterator< T >::operator++()
  {
    m_node = m_node->next;
    return *this;
  }

  template < typename T >
  ConstIterator< T > &ConstIterator< T >::operator--()
  {
    m_node = m_node->prev;
    return *this;
  }

  template < typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    ConstIterator< T > temp(*this);
    operator++();
    return temp;
  }

  template < typename T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    ConstIterator< T > temp(*this);
    operator--();
    return temp;
  }

  template < typename T >
  const T &ConstIterator< T >::operator*()
  {
    return m_node->value;
  }

  template < typename T >
  const T *ConstIterator< T >::operator->()
  {
    return &m_node->value;
  }

  template < typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T > &it)
  {
    return m_node == it.m_node;
  }

  template < typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T > &it)
  {
    return !operator==(it);
  }

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
  List< T > &List< T >::operator=(const List< T > &other)
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
  void List< T >::insert(const_iterator pos, T &&value)
  {
    auto newTail = new Node< T >(value);
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
    Node< T > prev = m_tail->prev;
    delete m_tail;
    m_tail = prev;
    --m_size;
  }

  template < typename T >
  void List< T >::pop_front()
  {
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

  template < typename T >
  typename List< T >::const_iterator List< T >::cbegin() const
  {
    return const_iterator(m_head);
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::cend() const
  {
    return const_iterator(nullptr);
  }
}

#endif
