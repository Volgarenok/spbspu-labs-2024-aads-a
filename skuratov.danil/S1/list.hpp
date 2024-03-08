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
      Node* ptr = head;
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
      Node* right = getAt(index)
    }

  };
}

#endif
