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

    //size() - возвр размер списка

    Iterator< T > begin() const; // должен возв итератор на первый элемент
    Iterator< T > end() const; // должен возв итератор на послед элемент

    //font - получение значения первого эл
    //back - получение значения посл эл

    void push_back(const T &el); // - доб в конец.
    void push_front(const T &el); // - доб в нач.

    //insert - втсавтка эл в произвольную поз.
    void clear(); // - нахрен все

    void pop_front(); // - удаление первого
    void pop_back(); // - удаление последнего

    //earse - удаление произвольного

    void printList(std::ostream &out) const;

    ~BinList();

    Node<T> *head_;
    Node<T> *tail_;
    size_t size;
  };
}
#endif
