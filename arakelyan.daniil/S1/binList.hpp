#ifndef BINLIST_HPP
#define BINLIST_HPP

#include <iostream>
#include <initializer_list>
#include "iterator.hpp"
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList
  {
    using iterator = Iterator< T >;
    using const_iterator = const Iterator< T >;

    BinList();
    BinList(int size);
    BinList(size_t size, const T &val); // fine
    BinList(const BinList< T > &ls); // fine

    size_t getSize() const; // fine
    bool isEmpty() const;   // fine

    iterator begin() const; // должен возв итератор на первый элемент - fine
    const_iterator cbegin() const; // fine
    iterator end() const; // должен возв итератор на послед элемент - fine
    const_iterator cend() const; // fine

    T getFirst() const; // fine
    T getLast() const;  // fine

    void push_back(const T &el);  // доб в конец. - fine
    void push_front(const T &el); // доб в нач. - fine
    //void insert(iterator it_pos, const T &val); // втсавтка эл в произвольную поз.

    void clear(); // нахрен все - fine

    void pop_front(); // удаление первого - fine
    void pop_back();  // удаление последнего - fine

    void erase(iterator it_pos); // удаление произвольного, принимает итератор
    void erase(iterator it_start, iterator it_end); // удаление элементов из заданного диапозона

    void assign(const T &val, size_t size); // делает список значениями val и размером size - fine
    void assign(iterator it_start, iterator it_end); // делает список из диап итераторов другого списка - fine
    void assign(std::initializer_list<T> l); // делает список из значений списковой инициализации - fine

    // operator!=
    // operator ==
    // operator =

    void printList(std::ostream &out) const; // fine

    ~BinList(); // fine
  private:
    Node< T > *head_;
    Node< T > *tail_;
    size_t size_;
  };
}
#endif
