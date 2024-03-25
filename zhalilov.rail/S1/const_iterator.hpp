#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class List;

  template < typename T >
  class ConstIterator
  {
  public:
    ~ConstIterator() = default;

    ConstIterator &operator=(const ConstIterator &) = default;

    ConstIterator &operator++();
    ConstIterator &operator--();
    ConstIterator operator++(int);
    ConstIterator operator--(int);

    const T &operator*();
    const T *operator->();

    bool operator==(const ConstIterator< T > &) const;
    bool operator!=(const ConstIterator< T > &) const;

    friend List< T >;

  private:
    Node< T > *m_node;

    explicit ConstIterator(Node< T > *);
  };

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
  bool ConstIterator< T >::operator==(const ConstIterator< T > &it) const
  {
    return m_node == it.m_node;
  }

  template < typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T > &it) const
  {
    return !operator==(it);
  }
}

#endif
