#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"

namespace skuratov
{
  template <typename T>
  class List
  {
  public:
    size_t size_;
    Node< T >* head;
    Node< T >* tail;
  public:
    List()
    {
      head = tail = NULL;
    }

    ~List()
    {
      while (head != NULL)
      {
        pop_front();
      }
    }

    Node< T >* push_front(size_t data)
    {
      Node< T >* ptr = new Node(data);
      ptr->next = head;
      if (head != NULL)
      {
        head->prev = ptr;
      }
      if (tail == NULL)
      {
        tail = ptr;
      }
      head = ptr;

      return ptr;
    }

    Node< T >* push_back(size_t data)
    {
      Node< T >* ptr = new Node(data);
      ptr->prev = tail;
      if (tail != NULL)
      {
        tail->next = ptr;
      }
      if (head == NULL)
      {
        head = ptr;
      }
      tail = ptr;

      return ptr;
    }

    void pop_front()
    {
      if (head == NULL)
      {
        return;
      }
      Node< T >* ptr = head->next;
      if (ptr != NULL)
      {
        ptr->prev = NULL;
      }
      else
      {
        tail = NULL;
      }
      delete head;
      head = ptr;
    }

    void pop_back()
    {
      if (tail == NULL)
      {
        return;
      }
      Node< T >* ptr = tail->prev;
      if (ptr != NULL)
      {
        ptr->next = NULL;
      }
      else
      {
        head = NULL;
      }
      delete tail;
      tail = ptr;
    }

    Node< T >* getAt(size_t index)
    {
      Node< T >* ptr = head;
      for (size_t j = 0; j != index; j++)
      {
        if (ptr == NULL)
        {
          return ptr;
        }
        ptr = ptr->next;
      }
      return ptr;
    }

    Node< T >* operator [] (int index)
    {
      return getAt(index);
    }

    Node< T >* insert(int index, double data)
    {
      Node< T >* right = getAt(index);
      if (right == NULL)
      {
        return push_back(data);
      }
      Node< T >* left = right->prev
      if (left == NULL)
      {
        return push_front(data);
      }

      Node< T >* ptr = new Node(data);
      ptr->prev = left;
      ptr->next = right;
      left->prev = ptr;
      right->next = ptr;

      return ptr;
    }

    void erase(int index)
    {
      Node< T >* ptr = getAt(index);
      if (ptr == NULL)
      {
        return;
      }
      if (ptr->prev == NULL)
      {
        pop_front();
        return;
      }
      if (ptr->prev == NULL)
      {
        pop_back();
        return;
      }
      Node< T >* left = ptr->prev;
      Node< T >* right = ptr->next;
      left->next = right;
      right->prev = left;

      delete ptr;
    }
  };
}

#endif
