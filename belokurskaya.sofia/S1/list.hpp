#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

namespace belokurskaya
{
  template< typename T >
  class List
  {
    struct Node
    {
      T value;
      Node * next;
      Node(T value) : value(value), next(nullptr) {}
    };
    Node * head;
    Node * tail;

    public:
      List();
      List(size_t count, const T & value);
      List(const std::initializer_list< T >& ilist);
      ~List();
      bool empty() const;
      void push_back(T value);
      void push_front(T value);
      void pop_back();
      void pop_front();
      void insert(size_t index, T value);
      void erase(size_t index);
      void remove(T value);
      T & at(size_t index) const;
      size_t size() const;
      bool operator==(const List< T >& other) const;
      bool operator!=(const List< T >& other) const;
      bool operator<(const List< T >& other) const;
      bool operator<=(const List< T >& other) const;
      bool operator>(const List< T >& other) const;
      bool operator>=(const List< T >& other) const;
  };
}

#endif
