#ifndef BINLIST_HPP
#define BINLIST_HPP

#include <iostream>
#include <initializer_list>
#include "iterator.hpp"
#include "constIterator.hpp"
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList
  {
    using iterator = Iterator< T >;
    using const_iterator =  ConstIterator< T >;

    BinList();
    BinList(const T &val, size_t size);
    BinList(Node< T > *head, Node< T > *tail);
    BinList(const BinList< T > &ls);
    BinList(std::initializer_list< T > ls);
    BinList(iterator it_start, iterator it_end);

    size_t getSize() const;//fine
    bool isEmpty() const;//fine

    iterator begin() const;//fine
    const_iterator cbegin() const;//fine
    iterator end() const;//fine
    const_iterator cend() const;//fine

    //spile
    //reverse

    T getFirst() const;//fine
    T getLast() const;//fine

    void push_back(const T &el);//fine
    void push_front(const T &el);//fine
    iterator insert_after(const_iterator it_pos, const T &val);//fine

    void clear();//fine

    void pop_front();//fine
    void pop_back();//fine
    void remove(const T &val);
    template < class Unarypredicate >
    void remove_if(Unarypredicate p);

    void swap(BinList &ls);//fine

    iterator erase(iterator it_pos);//fine
    iterator erase(iterator it_start, iterator it_end);//fine

    void assign(const T &val, size_t size);//fine
    void assign(iterator it_start, iterator it_end);//fine
    void assign(std::initializer_list< T > ls);//fine

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
