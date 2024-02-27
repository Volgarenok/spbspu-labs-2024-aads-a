#ifndef BINLIST_HPP
#define BINLIST_HPP

#include <iostream>
#include "node.hpp"

namespace arakelyan
{
  template < class T >
  struct BinList
  {
    struct Iterator
    {
      Node< T > *node;

      Iterator(const Iterator &val) = default;
      Iterator & operator=(const Iterator &val) = default;

      // operator--
      // operator--(int)

      ~Iterator() = default;
      Iterator():
        node(nullptr)
      {}

      Iterator & operator++()
      {
        if (node == nullptr)
        {
          throw std::logic_error("node == nullptr!");
        }
        node = node->nextPtr;
        return *this;
      }

      Iterator operator++(int)
      {
        if (node == nullptr)
        {
          throw std::logic_error("node == nullptr!");
        }
        Iterator res(*this);
        ++(*this);
        return res;
      }

      T &operator*()
      {
        if (node == nullptr)
        {
          throw std::logic_error("node == nullptr");
        }
        return node->value;
      }

      T *operator->()
      {
        if (node == nullptr)
        {
          throw std::logic_error("node == nullptr");
        }
        return std::addressof(*this);
      }


      bool operator!=(const Iterator &val) const
      {
        return node == val.node;
      }

      bool operator==(const Iterator &val) const
      {
        return !(val == *this);
      }
    };

    Node<T> *head_;
    Node<T> *tail_;
    size_t size;


    BinList();

    //size() - возвр размер списка

    Iterator &begin() const; // должен возв итератор на первый элемент
    Iterator end() const; // должен возв итератор на послед элемент

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
  };
}
#endif
