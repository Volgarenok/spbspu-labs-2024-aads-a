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
    iterator operator+(size_t n);
    iterator operator-(size_t n);

    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    T& operator*() const;
    T* operator->() const;
  };

  template <typename T>
  iterator<T>::iterator()
  {}

  template <typename T>
  iterator<T>::iterator(Node<T>* node) : current(node)
  {}

  template <typename T>
  iterator<T>::iterator(const iterator& other) : current(other.current)
  {}

  template <typename T>
  iterator<T>& iterator<T>::operator++()
  {
    if (current) current = current->next;
    return *this;
  }

  template <typename T>
  iterator<T>& iterator<T>::operator--()
  {
    if (current)
    {
      current = current->prev;
    }

    return *this;
  }

  template <typename T>
  iterator<T> iterator<T>::operator+(size_t n)
  {
    iterator temp = *this;
    for (size_t i = 0; i < n; ++i)
    {
      ++temp;
    }
    return temp;
  }

  template <typename T>
  iterator<T> iterator<T>::operator-(size_t n)
  {
    iterator temp = *this;
    for (size_t i = 0; i < n; ++i)
    {
      --temp;
    }
    return temp;
  }

  template <typename T>
  bool iterator<T>::operator==(const iterator& other) const
  {
    return current == other.current;
  }

  template <typename T>
  bool iterator<T>::operator!=(const iterator& other) const
  {
    return current != other.current;
  }

  template <typename T>
  T& iterator<T>::operator*() const
  {
    return current->data;
  }

  template <typename T>
  T* iterator<T>::operator->() const
  {
    return &(current->data);
  }
}

#endif