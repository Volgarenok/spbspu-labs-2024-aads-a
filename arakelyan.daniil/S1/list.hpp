#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include <iostream>

namespace arakelyan
{
  template < class T >
  struct List
  {
    Node<T> *head;
    Node<T> *tail;

    List();
    bool isEmpty() const;
    void push_back(const T & el);
    void push_front(const T & el);
    void pop_front();
    void pop_back();
    void printList(std::ostream & out) const;
    // void deleteNode(Node * val);
    // Node * getLastNode() const;
    ~List();
  };
}
#endif
