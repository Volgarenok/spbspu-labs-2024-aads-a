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
    BinList(const T &val, size_t size);
    BinList(Node< T > *head, Node< T > *tail);
    BinList(const BinList< T > &ls);
    BinList(std::initializer_list< T > ls);
    BinList(iterator it_start, iterator it_end);

    size_t getSize() const;
    bool isEmpty() const;

    iterator begin() const;
    const_iterator cbegin() const;
    iterator end() const;
    const_iterator cend() const;

    //spile
    //reverse

    T getFirst() const;
    T getLast() const;

    void push_back(const T &el);
    void push_front(const T &el);
    iterator insert_after(iterator it_pos, const T &val); // втсавтка эл в произвольную поз. - added

    void clear();

    void pop_front();
    void pop_back();
    // void remove()
    //remove if

    void swap(BinList &ls);

    iterator erase(iterator it_pos); // удаление произвольного, принимает итератор - added
    iterator erase(iterator it_start, iterator it_end); // удаление элементов из заданного диапозона - added

    void assign(const T &val, size_t size);
    void assign(iterator it_start, iterator it_end);
    void assign(std::initializer_list< T > ls);

    // operator!=
    // operator ==
    // operator =

    void printList(std::ostream &out) const;

    ~BinList();
  private:
    Node< T > *head_;
    Node< T > *tail_;
    size_t size_;
  };
}
#endif
