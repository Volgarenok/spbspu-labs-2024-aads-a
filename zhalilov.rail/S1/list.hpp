#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>

#include "iterator.hpp"
#include "const_iterator.hpp"
#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using const_iterator = ConstIterator< T >;
    List();
    List(const List< T > &);
    List(List< T > &&);
    List(size_t);
    List(size_t, const T &);
    ~List();

    List< T > &operator=(const List< T > &);
    List< T > &operator=(List< T > &&);

    T &front();
    T &back();

    size_t capacity();
    bool empty() const;

    iterator insert(const_iterator, const T &);
    iterator insert(const_iterator, T &&);
    void push_back(const T &);
    void push_front(const T &);

    iterator erase(const_iterator);
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
  };

  template < typename T >
  List< T >::List():
    m_size(0),
    m_head(nullptr)
  {
    m_head = new Node< T >;
    m_head->next = m_head;
    m_head->prev = m_head;
  }

  template < typename T >
  List< T >::List(const List< T > &other):
    List()
  {
    if (!other.empty())
    {
      const_iterator curr = other.cbegin();
      const_iterator end = other.cend();
      while (curr != end)
      {
        push_back(*curr);
        curr++;
      }
    }
  }

  template < typename T >
  List< T >::List(List< T > &&other):
    m_size(other.m_size),
    m_head(other.m_head)
  {
    other.m_size = 0;
    other.m_head = nullptr;
  }

  template < typename T >
  List<T>::List(size_t n)
    :List(n, T())
  {}

  template < typename T >
  List<T>::List(size_t n, const T &value)
    :List()
  {
    for (size_t i = 0; i < n; i++)
    {
      push_back(value);
    }
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
    delete m_head;
  }

  template < typename T >
  List< T > &List< T >::operator=(const List< T > &other)
  {
    m_size = other.m_size;
    m_head = other.m_head;
    iterator curr = other.begin();
    iterator end = other.end();
    while (curr != end)
    {
      push_back(*curr);
      curr++;
    }
    return *this;
  }

  template < typename T >
  List< T > &List< T >::operator=(List< T > &&other)
  {
    clear();
    m_size = other.m_size;
    m_head = other.m_head;
    other.m_size = 0;
    other.m_head = nullptr;
    return *this;
  }

  template < typename T >
  T &List< T >::front()
  {
    return m_head->next->value;
  }

  template < typename T >
  T &List< T >::back()
  {
    return m_head->prev->value;
  }

  template < typename T >
  size_t List< T >::capacity()
  {
    return m_size;
  }

  template < typename T >
  bool List< T >::empty() const
  {
    return m_size == 0;
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, const T &value)
  {
    auto newNode = new Node< T >(value);
    Node< T > *prev = pos.m_node->prev;
    newNode->next = pos.m_node;
    newNode->prev = prev;
    prev->next = newNode;
    pos.m_node->prev = newNode;
    m_size++;
    return iterator(newNode);
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, T &&value)
  {
    insert(pos, value);
  }

  template < typename T >
  void List< T >::push_back(const T &value)
  {
    insert(cend(), value);
  }

  template < typename T >
  void List< T >::push_front(const T &value)
  {
    insert(cbegin(), value);
  }

  template < typename T >
  typename List<T>::iterator List<T>::erase(const_iterator it)
  {
    Node< T > *prev = it.m_node->prev;
    Node< T > *next = it.m_node->next;
    delete it.m_node;
    prev->next = next;
    next->prev = prev;
    m_size--;
    return iterator(next);
  }

  template < typename T >
  void List< T >::pop_back()
  {
    erase(--cend());
  }

  template < typename T >
  void List< T >::pop_front()
  {
    erase(cbegin());
  }

  template < typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_back();
    }
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
    return iterator(m_head->next);
  }

  template < typename T >
  typename List< T >::iterator List< T >::end()
  {
    return iterator(m_head);
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::cbegin() const
  {
    return const_iterator(m_head->next);
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::cend() const
  {
    return const_iterator(m_head);
  }
}

#endif
