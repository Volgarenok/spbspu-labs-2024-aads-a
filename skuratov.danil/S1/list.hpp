#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <vector>
#include <cstddef>
#include "node.hpp"

namespace skuratov
{
  template <typename T>
  class List
  {
  public:
    List();
    ~List();

    using iterator = Node<T>*;
    using const_iterator = const Node<T>*;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    bool empty() const;

    void push_back(const T& value);

    void clear();

    std::size_t size() const;

    void pop_back();
    void assign(iterator first, iterator last);
    void swap(List<T>& other);

  private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
  };
}

#endif
