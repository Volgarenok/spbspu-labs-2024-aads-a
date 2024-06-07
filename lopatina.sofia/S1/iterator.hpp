#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <forward_list>
#include <assert.h>
#include "node.hpp"

namespace lopatina
{
  template <typename T>
  struct List;

  template <typename T>
  struct ListIterator: public std::iterator<std::forward_iterator_tag,T>
  {
  public:
    using this_t = ListIterator<T>;
    ListIterator():
      node(nullptr)
    {}
    ListIterator(Node<T> * node):
      node(node)
    {}
    ~ListIterator() = default;

    ListIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++()
    {
      assert(node != nullptr);
      node = node->next;
      return *this;
    }
    this_t operator++(int)
    {
      assert(node != nullptr);
      this_t result(*this);
      ++(*this);
      return result;
    }
    T & operator*()
    {
      assert(node != nullptr);
      return node->data;
    }
    T * operator->()
    {
      assert(node != nullptr);
      return std::addressof(node->data);
    }

    bool operator==(const this_t & rhs) const
    {
      return node == rhs.node;
    }
    bool operator!=(const this_t & rhs) const
    {
      return !(rhs == *this);
    }

  private:
    Node<T> * node;
  };
}

#endif
