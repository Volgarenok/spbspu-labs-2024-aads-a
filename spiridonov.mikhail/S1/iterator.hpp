#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"

namespace spiridonov
{
  template <typename T>
  class iterator
  {
  private:
    Node<T>* current;

  public:
    iterator();
    iterator(Node<T>* node);
    iterator(const iterator& other);
    ~iterator() = default;

    iterator& operator++();
    iterator& operator--();
    iterator& operator+(size_t n);
    iterator& operator-(size_t n);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    T& operator*() const;
    T* operator->() const;
  };

  template <typename T>
  iterator<T>::iterator()
  {}

}

#endif
