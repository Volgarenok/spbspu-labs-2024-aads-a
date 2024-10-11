#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"

namespace stepanov
{
  template <typename T>
  class List
  {
  public:
    List();
    List(const List & other);
    List(List && other) noexcept;
    ~List();

    List & operator=(const List & other);
    List & operator=(List && other) noexcept;

    T & front();
    const T & front() const;
    bool empty() const noexcept;
    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void pop_front();
    void clear() noexcept;
    void swap(List & fwdlst);

    void remove(const T & value);
    template < typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t n, const T & value);

  private:
    Node<T> * head;
    Node<T> * tail;
  };
}


#endif

