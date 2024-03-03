#ifndef ITERATOR_HPP
#define ITERATOR_HPP

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
}

#endif
