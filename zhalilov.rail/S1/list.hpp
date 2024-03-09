#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>

#include "iterator.hpp"
#include "const_iterator.hpp"
#include "node.hpp"

namespace zhalilov
{
  template < typename T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using const_iterator = ConstIterator< T >;
    List();
    List(const List< T > &);
    List(List< T > &&);
    List(size_t);
    List(size_t, const T &);
    List(iterator, iterator);
    List(std::initializer_list< T >);
    ~List();

    List< T > &operator=(const List< T > &);
    List< T > &operator=(List< T > &&);

    bool operator==(const List< T > &);
    bool operator!=(const List< T > &);
    bool operator<(const List< T > &);
    bool operator<=(const List< T > &);
    bool operator>(const List< T > &);
    bool operator>=(const List< T > &);

    T &front();
    T &back();

    size_t capacity();
    bool empty() const;

    void assign(size_t, const T &);
    void assign(iterator, iterator);
    void assign(std::initializer_list< T >);

    void splice(const_iterator, List< T > &);
    void splice(const_iterator, List< T > &&);
    void splice(const_iterator, List< T > &, const_iterator otherListPos);
    void splice(const_iterator, List< T > &&, const_iterator otherListPos);
    void splice(const_iterator, List< T > &, const_iterator first, const_iterator last);
    void splice(const_iterator, List< T > &&, const_iterator first, const_iterator last);

    iterator insert(const_iterator, const T &);
    iterator insert(const_iterator, T &&);
    iterator insert(const_iterator, size_t, const T &);
    iterator insert(const_iterator, iterator first, iterator last);
    iterator insert(const_iterator, std::initializer_list< T >);

    void push_back(const T &);
    void push_back(T &&);
    void push_front(const T &);
    void push_front(T &&);

    template < typename Predicate >
    void remove_if(Predicate);
    void remove(const T &);

    iterator erase(const_iterator);
    void pop_back();
    void pop_front();
    void clear();
    void swap(List< T > &other);

    void reverse();

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

  private:
    size_t m_size;
    Node< T > *m_head;

    void inserter(const_iterator, Node< T > *);
    const_iterator splicer(const_iterator, const_iterator);
  };

  template < typename T >
  List< T >::List():
    m_size(0),
    m_head(nullptr)
  {
    m_head = new Node< T >;
    m_head->next = m_head;
    m_head->prev = m_head;
  }

  template < typename T >
  List< T >::List(const List< T > &other):
    List()
  {
    if (!other.empty())
    {
      const_iterator curr = other.cbegin();
      const_iterator end = other.cend();
      while (curr != end)
      {
        push_back(*curr);
        curr++;
      }
    }
  }

  template < typename T >
  List< T >::List(List< T > &&other):
    m_size(other.m_size),
    m_head(other.m_head)
  {
    other.m_size = 0;
    other.m_head = nullptr;
  }

  template < typename T >
  List< T >::List(size_t n):
    List(n, T())
  {}

  template < typename T >
  List< T >::List(size_t n, const T &value):
    List()
  {
    assign(n, value);
  }

  template < typename T >
  List< T >::List(iterator first, iterator last):
    List()
  {
    assign(first, last);
  }

  template < typename T >
  List< T >::List(std::initializer_list< T > il):
    List()
  {
    assign(il);
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
    delete m_head;
  }

  template < typename T >
  List< T > &List< T >::operator=(const List< T > &other)
  {
    List< T > tmp(other);
    swap(tmp);
    return *this;
  }

  template < typename T >
  List< T > &List< T >::operator=(List< T > &&other)
  {
    clear();
    m_size = other.m_size;
    m_head = other.m_head;
    other.m_size = 0;
    other.m_head = nullptr;
    return *this;
  }

  template < typename T >
  bool List< T >::operator==(const List< T > &list)
  {
    if (m_size == list.m_size)
    {
      List< T >::const_iterator thisIt = cbegin();
      List< T >::const_iterator thisEnd = cend();
      List< T >::const_iterator otherIt = list.cbegin();
      List< T >::const_iterator otherEnd = list.cend();
      while (thisIt != thisEnd)
      {
        if (*thisIt != *otherIt)
        {
          return false;
        }
        thisIt++;
        otherIt++;
      }
      return true;
    }
    return false;
  }

  template < typename T >
  bool List< T >::operator!=(const List< T > &list)
  {
    return !(*this == list);
  }

  template < typename T >
  bool List< T >::operator<(const List< T > &list)
  {
    if (m_size < list.m_size)
    {
      List< T >::const_iterator thisIt = cbegin();
      List< T >::const_iterator thisEnd = cend();
      List< T >::const_iterator otherIt = list.cbegin();
      List< T >::const_iterator otherEnd = list.cend();
      while (thisIt != thisEnd)
      {
        if (*thisIt != *otherIt)
        {
          return false;
        }
        thisIt++;
        otherIt++;
      }
      return true;
    }
    return false;
  }

  template < typename T >
  bool List< T >::operator<=(const List< T > &list)
  {
    return *this == list || *this < list;
  }

  template < typename T >
  bool List< T >::operator>(const List< T > &list)
  {
    if (m_size > list.m_size)
    {
      List< T >::const_iterator thisIt = cbegin();
      List< T >::const_iterator thisEnd = cend();
      List< T >::const_iterator otherIt = list.cbegin();
      List< T >::const_iterator otherEnd = list.cend();
      while (otherIt != otherEnd)
      {
        if (*thisIt != *otherIt)
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  template < typename T >
  bool List< T >::operator>=(const List< T > &list)
  {
    return *this == list || *this > list;
  }

  template < typename T >
  T &List< T >::front()
  {
    return m_head->next->value;
  }

  template < typename T >
  T &List< T >::back()
  {
    return m_head->prev->value;
  }

  template < typename T >
  size_t List< T >::capacity()
  {
    return m_size;
  }

  template < typename T >
  bool List< T >::empty() const
  {
    return m_size == 0;
  }

  template < typename T >
  void List< T >::assign(size_t n, const T &value)
  {
    clear();
    for (size_t i = 0; i < n; i++)
    {
      push_back(value);
    }
  }

  template < typename T >
  void List< T >::assign(iterator first, iterator last)
  {
    clear();
    while (first != last)
    {
      push_back(*first);
      first++;
    }
  }

  template < typename T >
  void List< T >::assign(std::initializer_list< T > il)
  {
    clear();
    typename std::initializer_list< T >::iterator ilIt = il.begin();
    while (ilIt != il.end())
    {
      push_back(*ilIt);
      ilIt++;
    }
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, const T &value)
  {
    auto newNode = new Node< T >(value);
    inserter(pos, newNode);
    return iterator(newNode);
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, T &&value)
  {
    auto newNode = new Node< T >(std::move(value));
    inserter(pos, newNode);
    return iterator(newNode);
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, size_t n, const T &value)
  {
    for (size_t i = 0; i < n; i++)
    {
      auto newIt = insert(pos, value);
      pos = const_iterator(newIt.m_node);
    }
    return iterator(pos.m_node->prev);
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, iterator first, iterator last)
  {
    while (first != last)
    {
      auto newIt = insert(pos, *first);
      pos = const_iterator(newIt.m_node);
      first++;
    }
    return iterator(pos.m_node->prev);
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator pos, std::initializer_list< T > il)
  {
    typename std::initializer_list< T >::iterator ilIt = il.begin();
    while (ilIt != il.end())
    {
      auto newIt = insert(pos, *ilIt);
      pos = const_iterator(newIt.m_node);
      ilIt++;
    }
    return iterator(pos.m_node->prev);
  }

  template < typename T >
  void List< T >::splice(const_iterator pos, List< T > &list)
  {
    while (!list.empty())
    {
      splicer(pos, list.cbegin());
      list.m_size--;
      m_size++;
    }
  }

  template < typename T >
  void List< T >::splice(const_iterator pos, List< T > &&list)
  {
    splice(pos, list);
  }

  template < typename T >
  void List< T >::splice(const_iterator pos, List< T > &list, const_iterator otherListPos)
  {
    splicer(pos, otherListPos);
    list.m_size--;
    m_size++;
  }

  template < typename T >
  void List< T >::splice(const_iterator pos, List< T > &&list, const_iterator otherListPos)
  {
    splice(pos, list, otherListPos);
  }

  template < typename T >
  void List< T >::splice(const_iterator pos, List< T > &list, const_iterator otherPosFirst, const_iterator otherPosLast)
  {
    while (otherPosFirst != otherPosLast)
    {
      const_iterator nextPos = otherPosFirst;
      nextPos++;
      splicer(pos, otherPosFirst);
      otherPosFirst = nextPos;
      list.m_size--;
      m_size++;
    }
  }

  template < typename T >
  void List< T >::splice(const_iterator pos, List< T > &&list, const_iterator otherPosFirst,
                         const_iterator otherPosLast)
  {
    splice(pos, list, otherPosFirst, otherPosLast);
  }

  template < typename T >
  void List< T >::push_back(const T &value)
  {
    insert(cend(), value);
  }

  template < typename T >
  void List< T >::push_back(T &&value)
  {
    insert(cend(), std::move(value));
  }

  template < typename T >
  void List< T >::push_front(const T &value)
  {
    insert(cbegin(), value);
  }

  template < typename T >
  void List< T >::push_front(T &&value)
  {
    insert(cbegin(), std::move(value));
  }

  template < typename T >
  template < typename Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    List< T >::const_iterator it = cbegin();
    while (it != cend())
    {
      if (pred(*it))
      {
        ~(it.m_node->value);
        erase(it);
        break;
      }
    }
  }

  template < typename T >
  void List< T >::remove(const T &value)
  {
    auto predicate = [value](const T &listValue)-> bool { return listValue == value; };
    remove_if(predicate);
  }

  template < typename T >
  typename List< T >::iterator List< T >::erase(const_iterator it)
  {
    Node< T > *prev = it.m_node->prev;
    Node< T > *next = it.m_node->next;
    delete it.m_node;
    prev->next = next;
    next->prev = prev;
    m_size--;
    return iterator(next);
  }

  template < typename T >
  void List< T >::pop_back()
  {
    erase(--cend());
  }

  template < typename T >
  void List< T >::pop_front()
  {
    erase(cbegin());
  }

  template < typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }

  template < typename T >
  void List< T >::swap(List< T > &other)
  {
    List< T > temp(std::move(*this));
    *this = std::move(other);
    other = std::move(temp);
  }

  template < typename T >
  void List< T >::reverse()
  {
    List< T > newList;
    while (!empty())
    {
      newList.push_front(front());
      pop_front();
    }
    swap(newList);
  }

  template < typename T >
  typename List< T >::iterator List< T >::begin()
  {
    return iterator(m_head->next);
  }

  template < typename T >
  typename List< T >::iterator List< T >::end()
  {
    return iterator(m_head);
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::cbegin() const
  {
    return const_iterator(m_head->next);
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::cend() const
  {
    return const_iterator(m_head);
  }

  template < typename T >
  void List< T >::inserter(const_iterator pos, Node< T > *newNode)
  {
    Node< T > *prev = pos.m_node->prev;
    newNode->next = pos.m_node;
    newNode->prev = prev;
    prev->next = newNode;
    pos.m_node->prev = newNode;
    m_size++;
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::splicer(const_iterator pos, const_iterator otherListPos)
  {
    Node< T > *prev = pos.m_node->prev;
    prev->next = otherListPos.m_node;
    pos.m_node->prev = otherListPos.m_node;

    Node< T > *otherPrev = otherListPos.m_node->prev;
    Node< T > *otherNext = otherListPos.m_node->next;
    otherPrev->next = otherNext;
    otherNext->prev = otherPrev;

    otherListPos.m_node->next = pos.m_node;
    otherListPos.m_node->prev = prev;
    return pos;
  }
}

#endif
