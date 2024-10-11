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
    List(const List& other);
    List& operator=(const List& other);
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;
    ~List();

    void push_back(const T& value);
    void push_back(const T&& value);
    void remove(const T& value);
    template <typename Predicate>
    void remove_if(Predicate pred);
    T& front();
    const T& front() const;
    bool empty() const;
    size_t get_size() const;

  private:
    Node<T>* head;
    Node<T>* tail;
    size_t list_size;

    void clear();
  };
}


#endif

