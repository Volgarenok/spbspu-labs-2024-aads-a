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
    Iterator(Iterator < T > &) = default;
    Iterator(Node < T > *);
    ~Iterator() = default;

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++();
    Iterator &operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    T &operator*();
    Node < T > *operator->();
    friend bool operator==(const Iterator &, const Iterator &) const;
    friend bool operator!=(const Iterator &, const Iterator &) const;

  private:
    Node < T > *m_node;
  };
}

#endif
