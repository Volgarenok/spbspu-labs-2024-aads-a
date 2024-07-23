#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"
#include "iterator.hpp"

namespace lopatina
{
  template <typename T>
  struct List
  {
    Node<T> * head;
    Node<T> * tail;

    List():
      head(nullptr),
      tail(nullptr)
    {}

    ~List()
    {
      clear();
    }

    explicit List(size_t n, const T & val):
      head(nullptr),
      tail(nullptr)
    {
      for (size_t i = 0; i < n; ++i)
      {
        push_back(val);
      }
    }

    List(const List & other):
      head(nullptr),
      tail(nullptr)
    {
      try
      {
        Node<T> * newptr = other.head;
        while (newptr)
        {
          push_back(newptr->data);
          newptr = newptr->next;
        }
      }
      catch (...)
      {
        while (!empty())
        {
          pop_front();
        }
        throw;
      }
    }

    List<T> & operator=(const List & other)
    {
      if (this != std::addressof(other))
      {
        List tmp(other);
        swap(tmp);
      }
      return *this;
    }

    T & front()
    {
      return head->data;
    }
    bool empty() const noexcept
    {
      return head == nullptr;
    }
    void push_front(T value)
    {
      Node<T> * newptr = new Node<T>(value);
      newptr->next = head;
      head = newptr;
      if (tail == nullptr)
      {
        tail = newptr;
      }
    }
    void push_back(T value)
    {
      Node<T> * newptr = new Node<T>(value);
      if (empty())
      {
        head = newptr;
        tail = newptr;
        return;
      }
      tail->next = newptr;
      tail = newptr;
    }
    void pop_front()
    {
      if (head == nullptr)
      {
        return;
      }
      if (head == tail)
      {
        delete tail;
        head = nullptr;
        tail = nullptr;
        return;
      }
      Node<T> * newhead = head->next;
      delete head;
      head = newhead;
    }
    void pop_back()
    {
      if (tail == nullptr)
      {
        return;
      }
      if (head == tail)
      {
        delete tail;
        head = nullptr;
        head = nullptr;
        return;
      }
      Node<T> * newptr = head;
      while (newptr->next != tail)
      {
        newptr = newptr->next;
      }
      newptr->next = nullptr;
      delete tail;
      tail = newptr;
    }
    void clear() noexcept
    {
      Node<T> * newhead = head;
      while (newhead)
      {
        newhead = head->next;
        delete head;
        head = newhead;
      }
    }
    void swap(List & list2)
    {
      Node<T> * subhead = head;
      Node<T> * subtail = tail;
      head = list2.head;
      tail = list2.tail;
      list2.head = subhead;
      list2.tail = subtail;
    }

    void remove(const T & val)
    {
      if (head == nullptr)
      {
        return;
      }
      if (head == tail)
      {
        if (head->data == val)
        {
          pop_back();
        }
        return;
      }
      Node<T> * subhead = head;
      Node<T> * todelete = head;
      while (subhead)
      {
        if ((subhead == head) && (subhead->data == val))
        {
          subhead = subhead->next;
          pop_front();
        }
        else
        {
          if (subhead->next)
          {
            todelete = subhead->next;
            if (todelete->data == val)
            {
              subhead->next = todelete->next;
              delete todelete;
            }
            else
            {
              subhead = subhead->next;
            }
          }
          else
          {
            subhead = subhead->next;
          }
        }
      }
    }
    void assign(size_t n, const T & val)
    {
      clear();
      for (size_t i = 0; i < n; ++i)
      {
        push_back(val);
      }
    }

    ListIterator<T> begin()
    {
      return ListIterator<T>(head);
    }
    ListIterator<T> end()
    {
      return ListIterator<T>();
    }
  };
}

#endif
