#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class Iterator
  {
  public:
    Iterator();
    Iterator(Iterator< T > &) = default;
    Iterator(Node< T > *);
    ~Iterator() = default;

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++();
    Iterator &operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    T &operator*();
    T *operator->();

    template < typename X >
    friend bool operator==(const Iterator< X > &, const Iterator< X > &);
    template < typename X >
    friend bool operator!=(const Iterator< X > &, const Iterator< X > &);

  private:
    Node< T > *m_node;
  };

  template < typename T >
  Iterator< T >::Iterator():
    m_node(nullptr)
  {}

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
  bool operator==(const Iterator< T > &it1, const Iterator< T > &it2)
  {
    return it1.m_node == it2.m_node;
  }

  template < typename T >
  bool operator!=(const Iterator< T > &it1, const Iterator< T > &it2)
  {
    return !operator==(it1, it2);
  }
}

#endif
