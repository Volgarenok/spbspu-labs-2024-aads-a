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
    BinList();

    size_t getSize() const; // fine
    bool isEmpty() const; // fine

    Iterator< T > begin() const; // должен возв итератор на первый элемент - fine
    Iterator< T > end() const; // должен возв итератор на послед элемент - fine

    //first - получение значения первого эл
    T getFirst() const; // fine
    //last - получение значения посл эл
    T getLast() const; // fine

    void push_back(const T &el); // - доб в конец. - fine
    void push_front(const T &el); // - доб в нач. - fine

    //insert - втсавтка эл в произвольную поз.
    void clear(); // - нахрен все - fine

    void pop_front(); // - удаление первого - fine
    void pop_back(); // - удаление последнего - fine

    //earse - удаление произвольного

    void printList(std::ostream &out) const;

    ~BinList();

  private:
    Node<T> *head_;
    Node<T> *tail_;
    size_t size;
  };
}
#endif
