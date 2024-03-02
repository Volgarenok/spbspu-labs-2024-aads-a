#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"
#include "type_traits"

namespace zhalilov
{
  template < bool isConst, typename T >
  class Iterator
  {
  public:
    Iterator();
    Iterator(const Iterator< isConst, T > &) = default;
    Iterator(Node< T > *);
    ~Iterator() = default;

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++();
    Iterator &operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    typename std::enable_if< isConst, const T >::type &operator*() const;
    typename std::enable_if< !isConst, T >::type &operator*();
    typename std::enable_if< isConst, T >::type *operator->() const;
    typename std::enable_if< !isConst, T >::type *operator->();

    bool operator==(const Iterator< isConst, T > &);
    bool operator!=(const Iterator< isConst, T > &);

  private:
    Node< T > *m_node;
  };

  template < bool isConst, typename T >
  Iterator< isConst, T >::Iterator():
    m_node(nullptr)
  {}

  template < bool isConst, typename T >
  Iterator< isConst, T >::Iterator(Node< T > *node):
    m_node(node)
  {}

  template < bool isConst, typename T >
  Iterator< isConst, T > &Iterator< isConst, T >::operator++()
  {
    m_node = m_node->next;
    return *this;
  }

  template < bool isConst, typename T >
  Iterator< isConst, T > &Iterator< isConst, T >::operator--()
  {
    m_node = m_node->prev;
    return *this;
  }

  template < bool isConst, typename T >
  Iterator< isConst, T > Iterator< isConst, T >::operator++(int)
  {
    Iterator< isConst, T > temp(*this);
    operator++();
    return temp;
  }

  template < bool isConst, typename T >
  Iterator< isConst, T > Iterator< isConst, T >::operator--(int)
  {
    Iterator< isConst, T > temp(*this);
    operator--();
    return temp;
  }

  template < bool isConst, typename T >
  typename std::enable_if< isConst, const T >::type &Iterator< isConst, T >::operator*() const
  {
    return m_node->value;
  }

  template < bool isConst, typename T >
  typename std::enable_if< !isConst, T >::type &Iterator< isConst, T >::operator*()
  {
    return m_node->value;
  }

  template < bool isConst, typename T >
  typename std::enable_if< isConst, T >::type *Iterator< isConst, T >::operator->() const
  {
    return &m_node->value;
  }

  template < bool isConst, typename T >
  typename std::enable_if< !isConst, T >::type *Iterator< isConst, T >::operator->()
  {
    return &m_node->value;
  }

  template < bool isConst, typename T >
  bool Iterator< isConst, T >::operator==(const Iterator< isConst, T > &it)
  {
    return m_node == it.m_node;
  }

  template < bool isConst, typename T >
  bool Iterator< isConst, T >::operator!=(const Iterator< isConst, T > &it)
  {
    return !operator==(it);
  }
}

#endif
