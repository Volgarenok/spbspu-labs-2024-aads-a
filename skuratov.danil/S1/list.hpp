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

    Node* push_front(size_t data)
    {
      Node* ptr = new Node(data);
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

    Node* push_back(size_t data)
    {
      Node* ptr = new Node(data);
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


  };
}

#endif
