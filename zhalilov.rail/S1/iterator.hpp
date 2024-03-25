#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class List;

  template < typename T >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, T, T, T *, T >
  {
  public:
    ~Iterator() = default;

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++();
    Iterator &operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    T &operator*();
    T *operator->();

    bool operator==(const Iterator< T > &) const;
    bool operator!=(const Iterator< T > &) const;

    friend List< T >;

  private:
    Node< T > *m_node;

    explicit Iterator(Node< T > *);
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
  bool Iterator< T >::operator==(const Iterator< T > &it) const
  {
    return m_node == it.m_node;
  }

  template < typename T >
  bool Iterator< T >::operator!=(const Iterator< T > &it) const
  {
    return !operator==(it);
  }
}

#endif
