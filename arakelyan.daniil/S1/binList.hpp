#ifndef BINLIST_HPP
#define BINLIST_HPP

#include <iostream>

#include "node.hpp"
#include "iterator.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList
  {
    Node<T> *head_;
    Node<T> *tail_;
    Iterator< T > iterator_;

    BinList();

    // bool isEmpty() const;

    T & begin() const;
    T & end() const;

    void push_back(const T & el);
    void push_front(const T & el);
    void pop_front();
    void pop_back();

    void clear();
    void printList(std::ostream & out) const;
    // Node * getLastNode() const;

    ~BinList();
  };
}
#endif
